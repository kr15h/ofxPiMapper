#include "ProjectionEditorWidget.h"

namespace ofx {
namespace piMapper {

ProjectionEditorWidget::ProjectionEditorWidget(){
	surfaceManager = 0;
	bShiftKeyDown = false;
	fSnapDistance = 10.0f;
	enable();
}

void ProjectionEditorWidget::registerAppEvents(){
	ofAddListener(ofEvents().messageEvent, this, &ProjectionEditorWidget::gotMessage);
}

void ProjectionEditorWidget::unregisterAppEvents(){
	ofRemoveListener(ofEvents().messageEvent, this, &ProjectionEditorWidget::gotMessage);
}

void ProjectionEditorWidget::enable(){
	registerAppEvents();
}

void ProjectionEditorWidget::disable(){
	unregisterAppEvents();
}

void ProjectionEditorWidget::update(){
	// update surface if one of the joints is being dragged
	for(int i = 0; i < joints.size(); i++){
		if(joints[i]->isDragged() || joints[i]->isSelected()){
			if(surfaceManager->getSelectedSurface() != 0){
				// update vertex to new location
				surfaceManager->getSelectedSurface()->setVertex(i, joints[i]->position);
			}else{
				// clear joints if there is no surface selected
				// as the remove selected surface in the surface manager
				// is not supposed to access joints here
				joints.clear();
			}
			break;
		}
	}
}

void ProjectionEditorWidget::draw(){
	if(surfaceManager == 0){
		return;
	}
	if(surfaceManager->getSelectedSurface() == 0){
		return;
	}
	if(joints.size() <= 0){
		createJoints();
	}
	drawJoints();
}

void ProjectionEditorWidget::mouseDragged(ofMouseEventArgs & args){
	
	// Pass args to joint mouse events
	for(unsigned int i = 0; i < joints.size(); ++i){
		joints[i]->mouseDragged(args);
	}
	
	ofVec2f mousePosition = ofVec2f(args.x, args.y);

	// Collect all vertices of the projection surfaces
	vector <ofVec3f *> allVertices;
	for(int i = 0; i < surfaceManager->size(); i++){
		BaseSurface * surface = surfaceManager->getSurface(i);
		if(surface == surfaceManager->getSelectedSurface()){
			continue; // Don't add vertices of selected surface
		}
		for(int j = 0; j < surface->getVertices().size(); j++){
			allVertices.push_back(&surface->getVertices()[j]);
		}
	}

	// Snap currently dragged joint to nearest vertex
	for(int i = 0; i < joints.size(); i++){
		if(joints[i]->isDragged()){
			for(int j = 0; j < allVertices.size(); j++){
				float distance = mousePosition.distance(*allVertices[j]);
				if(distance < fSnapDistance){
					joints[i]->position = *allVertices[j];
					ofVec2f clickDistance = joints[i]->position - ofVec2f(args.x, args.y);
					joints[i]->setClickDistance(clickDistance);
					break;
				}
			}
		}
	}
}

void ProjectionEditorWidget::gotMessage(ofMessage & msg){
	if(msg.message == "surfaceSelected"){
		clearJoints();
		createJoints();
	}
}

void ProjectionEditorWidget::setSurfaceManager(SurfaceManager * newSurfaceManager){
	surfaceManager = newSurfaceManager;
}

void ProjectionEditorWidget::clearJoints(){
	while(joints.size()){
		delete joints.back();
		joints.pop_back();
	}
}

void ProjectionEditorWidget::createJoints(){
	if(surfaceManager == 0){
		return;
	}
	clearJoints();

	if(surfaceManager->getSelectedSurface() == 0){
		ofLog(OF_LOG_WARNING, "Trying to create joints while no surface selected.");
		return;
	}

	vector <ofVec3f> & vertices =
		surfaceManager->getSelectedSurface()->getVertices();

	for(int i = 0; i < vertices.size(); i++){
		joints.push_back(new CircleJoint());
		joints.back()->position = ofVec2f(vertices[i].x, vertices[i].y);
	}
}

void ProjectionEditorWidget::updateJoints(){
	if(surfaceManager->getSelectedSurface()){
		vector <ofVec3f> & vertices =
			surfaceManager->getSelectedSurface()->getVertices();
		for(int i = 0; i < vertices.size(); i++){
			joints[i]->position = ofVec2f(vertices[i].x, vertices[i].y);
		}
	}

}

void ProjectionEditorWidget::unselectAllJoints(){
	for(int i = 0; i < joints.size(); i++){
		joints[i]->unselect();
	}
}

void ProjectionEditorWidget::moveSelectedSurface(ofVec2f by){
	if(surfaceManager == 0){
		return;
	}
	if(surfaceManager->getSelectedSurface() == 0){
		return;
	}
	surfaceManager->getSelectedSurface()->moveBy(by);
	updateJoints();
}

void ProjectionEditorWidget::stopDragJoints(){
	for(int i = 0; i < joints.size(); i++){
		joints[i]->stopDrag();
	}
}

void ProjectionEditorWidget::setSnapDistance(float newSnapDistance){
	fSnapDistance = newSnapDistance;
}

CircleJoint * ProjectionEditorWidget::hitTestJoints(ofVec2f pos){
	for(int i = 0; i < joints.size(); i++){
		if(joints[i]->hitTest(pos)){
			return joints[i];
		}
	}
	return 0;
}

vector <CircleJoint *> * ProjectionEditorWidget::getJoints(){
	return &joints;
}

void ProjectionEditorWidget::drawJoints(){
	for(int i = 0; i < joints.size(); i++){
		joints[i]->draw();
	}
}

} // namespace piMapper
} // namespace ofx