#include "SetNextSourceCmd.h"

namespace ofx {
namespace piMapper {

SetNextSourceCmd::SetNextSourceCmd(BaseSurface * surface, SourcesEditorWidget * sourcesEditor){
	_surface = surface;
	_sourcesEditor = sourcesEditor;
}

void SetNextSourceCmd::exec(){
	ofLogNotice("SetNextSourceCmd", "exec");

	// Get current source
	BaseSource * source = _surface->getSource();
	int sourceType = source->getType();
	
	string sourceId;
	if(source->isLoadable()){
		sourceId = source->getPath();
	}else{
		sourceId = source->getName();
	}
	
	// MediaServer shortcut
	MediaServer * mediaServer = _sourcesEditor->getMediaServer();
	
	// Read sources into a single vector
	for(unsigned int i = 0; i < mediaServer->getImagePaths().size(); ++i){
		SourceData data;
		data.type = SourceType::SOURCE_TYPE_IMAGE;
		data.id = mediaServer->getImagePaths()[i];
		_sources.push_back(data);
	}
	for(unsigned int i = 0; i < mediaServer->getVideoPaths().size(); ++i){
		SourceData data;
		data.type = SourceType::SOURCE_TYPE_VIDEO;
		data.id = mediaServer->getVideoPaths()[i];
		_sources.push_back(data);
	}
	for(unsigned int i = 0; i < mediaServer->getFboSourceNames().size(); ++i){
		SourceData data;
		data.type = SourceType::SOURCE_TYPE_FBO;
		data.id = mediaServer->getFboSourceNames()[i];
		_sources.push_back(data);
	}
	
	if(_sources.size() <= 0){
		return;
	}
	
	_sourceIndex = -1;
	
	// Search for current source among all
	for(unsigned int i = 0; i < _sources.size(); ++i){
		if(sourceType == _sources[i].type && sourceId == _sources[i].id){
			_sourceIndex = i;
			break;
		}
	}
	
	if(_sourceIndex == -1){
		if(_sources.size()){
			_nextSourceIndex = 0;
		}else{
			return;
		}
	}
	
	_nextSourceIndex = _sourceIndex + 1;
	if(_nextSourceIndex >= _sources.size()){
		_nextSourceIndex = 0;
	}

    if(_sources[_nextSourceIndex].type == SourceType::SOURCE_TYPE_IMAGE){
		_sourcesEditor->setImageSource(_sources[_nextSourceIndex].id);
	}else if(_sources[_nextSourceIndex].type == SourceType::SOURCE_TYPE_VIDEO){
		_sourcesEditor->setVideoSource(_sources[_nextSourceIndex].id);
	}else if(_sources[_nextSourceIndex].type == SourceType::SOURCE_TYPE_FBO){
		_sourcesEditor->setFboSource(_sources[_nextSourceIndex].id);
	}else if(_sources[_nextSourceIndex].type == SourceType::SOURCE_TYPE_NONE){
		_sourcesEditor->clearSource();
	}
	
	Gui::instance()->getTextureEditorWidget().createJoints();
}

void SetNextSourceCmd::undo(){
	ofLogNotice("SetNextSourceCmd", "undo");

    if(_sources[_sourceIndex].type == SourceType::SOURCE_TYPE_IMAGE){
		_sourcesEditor->setImageSource(_sources[_sourceIndex].id);
	}else if(_sources[_sourceIndex].type == SourceType::SOURCE_TYPE_VIDEO){
		_sourcesEditor->setVideoSource(_sources[_sourceIndex].id);
	}else if(_sources[_sourceIndex].type == SourceType::SOURCE_TYPE_FBO){
		_sourcesEditor->setFboSource(_sources[_sourceIndex].id);
	}else if(_sources[_sourceIndex].type == SourceType::SOURCE_TYPE_NONE){
		_sourcesEditor->clearSource();
	}
	
	Gui::instance()->getTextureEditorWidget().createJoints();
}

} // namespace piMapper
} // namespace ofx

