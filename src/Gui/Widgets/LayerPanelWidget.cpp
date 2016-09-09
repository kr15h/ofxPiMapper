#include "LayerPanelWidget.h"

namespace ofx{
namespace piMapper{

LayerPanelWidget::LayerPanelWidget(){
	_sm = 0;
}

void LayerPanelWidget::draw(){
	if(_sm == 0){
		return;
	}
	
	int numSurfaces = _sm->size();
	
	for(int i = 0; i < numSurfaces; ++i){
		BaseSurface * surface = _sm->getSurface(i);
		BaseSurface * surfaceSelected = _sm->getSelectedSurface();
		
		ofPushStyle();
		ofSetColor(255, 255, 255);
		
		if(surface == surfaceSelected){
			ofFill();
		}else{
			ofNoFill();
		}
		
		int layerIconWidth = 45;
		int layerIconHeight = 20;
		int offsetRight = 20;
		int offsetTop = 40;
		int verticalSpacing = 10;
		int layerIconX = ofGetWidth() - offsetRight - layerIconWidth;
		int layerIconY = offsetTop + ((layerIconHeight + verticalSpacing) * (numSurfaces - i - 1));
		
		string label = "Layers";
		ofDrawBitmapString(label, ofGetWidth() - 66, 30);
		
		ofRectangle layerIcon = ofRectangle(
			layerIconX,
			layerIconY,
			layerIconWidth,
			layerIconHeight);
		
		ofDrawRectangle(layerIcon);
		
		ofPopStyle();
	}
}

} // namespace piMapper
} // namespace ofx