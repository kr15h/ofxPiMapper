#include "ScaleWidget.h"

namespace ofx {
namespace piMapper {

ScaleWidget::ScaleWidget(){
	_line.addVertex(ofPoint(0, 0));
	_line.addVertex(ofPoint(0, 0));
	
	_handle.width = 20;
	_handle.height = 20;
}

void ScaleWidget::setup(){

}

void ScaleWidget::update(){

}

void ScaleWidget::draw(){
	ofPushStyle();

	ofSetColor(255, 255, 255);
	ofNoFill();
	
	ofSetLineWidth(1);
	_line.draw();
	
	ofSetLineWidth(2);
	ofDrawRectangle(_handle);
	
	ofPopStyle();
}

void ScaleWidget::onMousePressed(ofMouseEventArgs & e){
	if(_handle.inside(e.x, e.y)){
		std::cout << "Handle clicked" << std::endl;
		_dragging = true;
	}
}

void ScaleWidget::onMouseReleased(ofMouseEventArgs & e){
	_dragging = false;
}

void ScaleWidget::onMouseDragged(ofMouseEventArgs & e){
	if(_dragging){
		_handle.x = e.x;
		_handle.y = e.y;
	}
}

bool ScaleWidget::inside(float x, float y){
	ofPoint p = ofPoint(x, y);
	return _handle.inside(p);
}

void ScaleWidget::setRect(ofRectangle rect){
	ofPoint center = rect.getCenter();
	
	_line.getVertices()[0].x = center.x;
	_line.getVertices()[0].y = center.y;
	
	_line.getVertices()[1].x = rect.x + rect.width;
	_line.getVertices()[1].y = rect.y;
	
	_handle.x = rect.x + rect.width;
	_handle.y = rect.y;
}

} // namespace piMapper
} // namespace ofx
