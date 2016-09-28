#include "Gui.h"

namespace ofx {
namespace piMapper {

Gui * Gui::_instance = 0;

Gui * Gui::instance(){
	if(_instance == 0){
		_instance = new ofx::piMapper::Gui();
	}
	return _instance;
}

Gui::Gui(){
	ofAddListener(_scaleWidget.guiWidgetEvent, this, &Gui::onScaleWidgetEvent);
}

Gui::~Gui(){
	ofRemoveListener(_scaleWidget.guiWidgetEvent, this, &Gui::onScaleWidgetEvent);
}

void Gui::notifyJointPressed(ofMouseEventArgs & args, int jointIndex){
	GuiJointEvent e;
	e.args = args;
	e.jointIndex = jointIndex;
	ofNotifyEvent(jointPressedEvent, e, this);
}

void Gui::notifyJointReleased(ofMouseEventArgs & args, int jointIndex){
	GuiJointEvent e;
	e.args = args;
	e.jointIndex = jointIndex;
	ofNotifyEvent(jointReleasedEvent, e, this);
}

void Gui::notifyJointDragged(ofMouseEventArgs & args, int jointIndex){
	GuiJointEvent e;
	e.args = args;
	e.jointIndex = jointIndex;
	ofNotifyEvent(jointDraggedEvent, e, this);
}

void Gui::notifySurfacePressed(ofMouseEventArgs & args, BaseSurface * surface){
	GuiSurfaceEvent e;
	e.args = args;
	e.surface = surface;
	ofNotifyEvent(surfacePressedEvent, e, this);
}

void Gui::notifySurfaceReleased(ofMouseEventArgs & args, BaseSurface * surface){
	GuiSurfaceEvent e;
	e.args = args;
	e.surface = surface;
	ofNotifyEvent(surfaceReleasedEvent, e, this);
}

void Gui::notifySurfaceDragged(ofMouseEventArgs & args, BaseSurface * surface){
	GuiSurfaceEvent e;
	e.args = args;
	e.surface = surface;
	ofNotifyEvent(surfaceDraggedEvent, e, this);
}

void Gui::notifyBackgroundPressed(ofMouseEventArgs & args){
	GuiBackgroundEvent e;
	e.args = args;
	ofNotifyEvent(backgroundPressedEvent, e, this);
}

void Gui::onMousePressed(ofMouseEventArgs & args){
	_scaleWidget.onMousePressed(args);
}

void Gui::onMouseReleased(ofMouseEventArgs & args){
	_scaleWidget.onMouseReleased(args);
}

void Gui::onMouseDragged(ofMouseEventArgs & args){
	_scaleWidget.onMouseDragged(args);
}

ScaleWidget & Gui::getScaleWidget(){
	return _scaleWidget;
}

LayerPanelWidget & Gui::getLayerPanelWidget(){
	return _layerPanelWidget;
}

SurfaceHighlightWidget & Gui::getSurfaceHighlightWidget(){
	return _surfaceHighlightWidget;
}

TextureHighlightWidget & Gui::getTextureHighlightWidget(){
	return _textureHighlightWidget;
}

TextureEditorWidget & Gui::getTextureEditorWidget(){
	return _textureEditorWidget;
}

ProjectionEditorWidget & Gui::getProjectionEditorWidget(){
	return _projectionEditorWidget;
}

SourcesEditorWidget & Gui::getSourcesEditorWidget(){
	return _sourcesEditorWidget;
}

void Gui::onScaleWidgetEvent(GuiWidgetEvent & event){
	GuiEvent e;
	e.args = event.args;
	e.widget = &_scaleWidget;
	ofNotifyEvent(guiEvent, e, this);
}

} // piMapper
} // ofx