#include "SurfaceHighlightWidget.h"

namespace ofx {
namespace piMapper {

SurfaceHighlightWidget::SurfaceHighlightWidget(){
	_sm = 0;
}

void SurfaceHighlightWidget::draw(){
	if(_sm == 0){
		return;
	}
	
	drawAllSurfaceOutlines();
	
	if(_sm->getSelectedSurface() == 0){
		return;
	}
	
	ofPushStyle();
	ofSetLineWidth(2);
	ofSetColor(255);
	
	drawSurfaceOutlines(_sm->getSelectedSurface());
	
	ofPopStyle();
}

void SurfaceHighlightWidget::drawAllSurfaceOutlines(){
	if(_sm == 0){
		return;
	}
	
	ofPushStyle();
	ofSetColor(255, 255, 255, 150);
	ofSetLineWidth(2);
	for(unsigned int i = 0; i < _sm->size(); ++i){
		if(_sm->getSurface(i) != _sm->getSelectedSurface()){
			drawSurfaceOutlines(_sm->getSurface(i));
		}
	}
	ofPopStyle();
}

void SurfaceHighlightWidget::drawSurfaceOutlines(BaseSurface * s){
	// TODO: Use Surface::drawOutline here
	if(s->getType() == SurfaceType::QUAD_SURFACE &&
		((QuadSurface *)s)->getPerspectiveWarping()){
		ofPolyline line = s->getHitArea();
		line.draw();
	}else if(s->getType() == SurfaceType::GRID_WARP_SURFACE){
		s->getMesh().drawWireframe();
	}else if(s->getType() == SurfaceType::HEXAGON_SURFACE){
		s->getMesh().drawWireframe();
	}else{
		ofPolyline p;
		for(unsigned int i = 0;
			i < s->getMesh().getVertices().size();
			++i){
			
			p.addVertex(ofPoint(
				s->getMesh().getVertices()[i]));
		}
		p.close();
		p.draw();
	}
}

} // namespace piMapper
} // namespace ofx
