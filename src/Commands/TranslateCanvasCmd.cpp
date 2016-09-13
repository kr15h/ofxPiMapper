#include "TranslateCanvasCmd.h"

namespace ofx {
namespace piMapper {

TranslateCanvasCmd::TranslateCanvasCmd(Application * app, ofPoint from, ofPoint to){
	_app = app;
	_from = from;
	_to = to;
}

void TranslateCanvasCmd::exec(){
	ofLogNotice("TranslateCanvasCmd", "exec");
	_app->getState()->setTranslation(_to);
}

void TranslateCanvasCmd::undo(){
	ofLogNotice("TranslateCanvasCmd", "undo");
	_app->getState()->setTranslation(_from);
}

} // namespace piMapper
} // namespace ofx

