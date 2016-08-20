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

void ScaleWidget::onMousePressed(ofMouseEventArgs & args){
	if(_handle.inside(args.x, args.y)){
		std::cout << "ScaleWidget: Handle clicked" << std::endl;
		_dragging = true;
	}
}

void ScaleWidget::onMouseReleased(ofMouseEventArgs & args){
	std::cout << "ScaleWidget: Mouse released" << std::endl;
	_dragging = false;
}

void ScaleWidget::onMouseDragged(ofMouseEventArgs & args){
	std::cout << "ScaleWidget: Mouse dragged" << std::endl;
	if(_dragging){
		_handle.x = args.x - (_handle.width / 2.0f);
		_handle.y = args.y - (_handle.height / 2.0f);
	}
	
	//Gui::instance()->notifyGuiWidgetEvent(args, this);
}

bool ScaleWidget::inside(float x, float y){
	ofPoint p = ofPoint(x, y);
	return _handle.inside(p);
}

void ScaleWidget::setRect(ofRectangle rect){
	if(_dragging){
		return;
	}
	
	ofPoint center = rect.getCenter();
	
	_line.getVertices()[0].x = center.x;
	_line.getVertices()[0].y = center.y;
	
	_line.getVertices()[1].x = rect.x + rect.width;
	_line.getVertices()[1].y = rect.y;
	
	_handle.x = rect.x + rect.width - (_handle.width / 2.0f);
	_handle.y = rect.y - (_handle.height / 2.0f);
}

} // namespace piMapper
} // namespace ofx
