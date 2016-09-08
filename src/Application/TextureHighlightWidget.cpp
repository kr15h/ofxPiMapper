#include "TextureHighlightWidget.h"

namespace ofx {
namespace piMapper {

TextureHighlightWidget::TextureHighlightWidget(){
	_sm = 0;
}

void TextureHighlightWidget::draw(){
	if(_sm == 0){
		return;
	}
	
	if(_sm->getSelectedSurface() == 0){
		return;
	}
	
	ofPolyline line = _sm->getSelectedSurface()->getTextureHitArea();
	ofPushStyle();
	ofSetLineWidth(2);
	ofSetColor(0, 255, 255);
	line.draw();
	ofPopStyle();
}

} // namespace piMapper
} // namespace ofx
