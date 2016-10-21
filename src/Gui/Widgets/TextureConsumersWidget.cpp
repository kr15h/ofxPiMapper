#include "TextureConsumersWidget.h"

namespace ofx {
namespace piMapper {

TextureConsumersWidget::TextureConsumersWidget(){
	_sm = 0;
}

void TextureConsumersWidget::draw(){
	if(_sm == 0){
		return;
	}
	
	if(_sm->getSelectedSurface() == 0){
		return;
	}

	ofPushStyle();
	ofSetLineWidth(2);
	ofSetColor(0, 255, 255, 150);
	for(unsigned int i = 0; i < _consumerSurfaces.size(); ++i){
		_consumerSurfaces[i]->getTextureHitArea().draw();
	}
	ofPopStyle();
}

void TextureConsumersWidget::findConsumerSurfaces(){
	if(_sm == 0){
		return;
	}
	
	if(_sm->getSelectedSurface() == 0){
		return;
	}
	
	BaseSource * activeSource = _sm->getSelectedSurface()->getSource();
	
	_consumerSurfaces.clear();
	for(unsigned int i = 0; i < _sm->getActivePreset()->size(); ++i){
		if(	activeSource == _sm->getActivePreset()->at(i)->getSource() &&
			_sm->getSelectedSurface() != _sm->getActivePreset()->at(i)){
			_consumerSurfaces.push_back(_sm->getActivePreset()->at(i));
		}
	}
}

} // namespace piMapper
} // namespace ofx
