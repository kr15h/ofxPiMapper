#include "ScaleWidget.h"

namespace ofx {
namespace piMapper {

ScaleWidget::ScaleWidget(){
	_line.addVertex(ofPoint(0, 0));
	_line.addVertex(ofPoint(0, 0));
	
	_handle.width = 20;
	_handle.height = 20;

	_scale = 1.0f;
	_surfaceManager = 0;
	_selectedSurface = 0;
}

void ScaleWidget::setup(){
	
}

void ScaleWidget::update(){
	if(_surfaceManager == 0){
		return;
	}
	
	if(_surfaceManager->getSelectedSurface() == 0){
		return;
	}
	
	if(_selectedSurface != _surfaceManager->getSelectedSurface()){
		_selectedSurface = _surfaceManager->getSelectedSurface();
		setRect(_surfaceManager->getSelectedSurface()->getBoundingBox());
	}
}

void ScaleWidget::draw(){
	if(_surfaceManager == 0){
		return;
	}

	if(_surfaceManager->getSelectedSurface() != 0){
		ofPoint centroid = _surfaceManager->getSelectedSurface()->getBoundingBox().getCenter();
		float lineLength = centroid.distance(
			ofPoint(
				_surfaceManager->getSelectedSurface()->getBoundingBox().x +
					_surfaceManager->getSelectedSurface()->getBoundingBox().width,
				_surfaceManager->getSelectedSurface()->getBoundingBox().y));
		
		// Handle surface move
		float dx = _line[0].x - centroid.x;
		float dy = _line[0].y - centroid.y;
		
		_line[0].x -= dx;
		_line[0].y -= dy;
		_line[1].x -= dx;
		_line[1].y -= dy;
		
		// Continue
		float scale = lineLength / _line[0].distance(_line[1]);
		
		_line[1].x = _line[0].x + (_line[1].x - _line[0].x) * scale;
		_line[1].y = _line[0].y + (_line[1].y - _line[0].y) * scale;
		
		_handle.x = _line[1].x - (_handle.width / 2.0f);
		_handle.y = _line[1].y - (_handle.height / 2.0f);
	}

	ofPushStyle();

	ofSetColor(255, 255, 255);
	ofNoFill();
	
	ofSetLineWidth(1);
	_line.draw();
	
	ofFill();
	ofDrawRectangle(
		_line.getVertices()[0].x - 5,
		_line.getVertices()[0].y - 5,
		10, 10);
	
	ofNoFill();
	ofSetLineWidth(2);
	ofDrawRectangle(_handle);
	
	ofPopStyle();
}

void ScaleWidget::onMousePressed(ofMouseEventArgs & args){
	if(_surfaceManager->getSelectedSurface() == 0){
		return;
	}
	
	if(_handle.inside(args.x, args.y)){
		_dragging = true;
		
		GuiWidgetEvent e;
		e.args = args;
		ofNotifyEvent(guiWidgetEvent, e, this);
	}
}

void ScaleWidget::onMouseReleased(ofMouseEventArgs & args){
	if(_dragging){
		GuiWidgetEvent e;
		e.args = args;
		ofNotifyEvent(guiWidgetEvent, e, this);
	}
	
	_dragging = false;
}

void ScaleWidget::onMouseDragged(ofMouseEventArgs & args){
	if(_dragging){
		if(_surfaceManager == 0){
			return;
		}
		
		if(_surfaceManager->getSelectedSurface() == 0){
			return;
		}
		
		ofRectangle box = _surfaceManager->getSelectedSurface()->getBoundingBox();
		float boxAspect = box.width / box.height;
		
		ofPolyline newLine = _line;
		newLine[1].x = args.x;
		newLine[1].y = args.y;
		
		_scale = _surfaceManager->getSelectedSurface()->getScale() /
			_line[0].distance(_line[1]) *
			newLine[0].distance(newLine[1]);
		
		_line = newLine;
		
		_handle.x = _line[1].x - (_handle.width / 2.0f);
		_handle.y = _line[1].y - (_handle.height / 2.0f);
		
		GuiWidgetEvent e;
		e.args = args;
		ofNotifyEvent(guiWidgetEvent, e, this);
	}
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

void ScaleWidget::setSurfaceManager(SurfaceManager * sm){
	_surfaceManager = sm;
	
	if(_surfaceManager->getSelectedSurface() == 0){
		return;
	}
	
	setRect(_surfaceManager->getSelectedSurface()->getBoundingBox());
}

} // namespace piMapper
} // namespace ofx
