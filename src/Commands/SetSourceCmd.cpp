#include "SetSourceCmd.h"

namespace ofx {
namespace piMapper {

SetSourceCmd::SetSourceCmd(int sourceType,
						   string sourceId,
						   BaseSurface * surface,
						   SourcesEditorWidget * sourcesEditor){

	_sourceType = sourceType;
	_sourceId = sourceId;
	_surface = surface;
	_sourcesEditor = sourcesEditor;
}

void SetSourceCmd::exec(){
	ofLogNotice("SetSourceCmd", "exec");

	_oldSourceTypeHelper = _surface->getSource()->getType();
	if(_surface->getSource()->isLoadable()){
		_oldSourceId = _surface->getSource()->getPath();
	}else{
		_oldSourceId = _surface->getSource()->getName();
	}

	if(_sourceType == SourceType::SOURCE_TYPE_IMAGE){
		_sourcesEditor->setImageSource(_sourceId);
	}else if(_sourceType == SourceType::SOURCE_TYPE_VIDEO){
		_sourcesEditor->setVideoSource(_sourceId);
	}else if(_sourceType == SourceType::SOURCE_TYPE_FBO){
		_sourcesEditor->setFboSource(_sourceId);
	}else if(_sourceType == SourceType::SOURCE_TYPE_NONE){
		_sourcesEditor->clearSource();
	}
}

void SetSourceCmd::undo(){
	ofLogNotice("SetSourceCmd", "undo");

	if(_oldSourceTypeHelper == SourceType::SOURCE_TYPE_IMAGE){
		_sourcesEditor->setImageSource(_oldSourceId);
	}else if(_oldSourceTypeHelper == SourceType::SOURCE_TYPE_VIDEO){
		_sourcesEditor->setVideoSource(_oldSourceId);
	}else if(_oldSourceTypeHelper == SourceType::SOURCE_TYPE_FBO){
		_sourcesEditor->setFboSource(_oldSourceId);
	}else if(_oldSourceTypeHelper == SourceType::SOURCE_TYPE_NONE){
		_sourcesEditor->clearSource();
	}

	_surface = 0;
	_sourcesEditor = 0;
}

} // namespace piMapper
} // namespace ofx

