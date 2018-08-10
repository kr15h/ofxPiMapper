#include "SetVideoSourceCmd.h"

namespace ofx {
namespace piMapper {

SetVideoSourceCmd::SetVideoSourceCmd(std::string sourceId,
						   bool loop,
						   BaseSurface * surface,
						   SourcesEditorWidget * sourcesEditor){
	_sourceId = sourceId;
	_loop = loop;
	_surface = surface;
	_sourcesEditor = sourcesEditor;
}

void SetVideoSourceCmd::exec(){
	ofLogNotice("SetVideoSourceCmd", "exec");

	_oldSourceTypeHelper = _surface->getSource()->getType();
	if(_surface->getSource()->isLoadable()){
		_oldSourceId = _surface->getSource()->getPath();
	}else{
		_oldSourceId = _surface->getSource()->getName();
	}

	_sourcesEditor->setVideoSource(_sourceId);
	BaseSource * src = _surface->getSource();
	VideoSource * vid = dynamic_cast<VideoSource *>(src);
	vid->setLoop(_loop);
}

void SetVideoSourceCmd::undo(){
	ofLogNotice("SetVideoSourceCmd", "undo");

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

