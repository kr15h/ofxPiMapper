#include "ProjectionEditor.h"

namespace ofx {
namespace piMapper {

ProjectionEditor::ProjectionEditor(){
	surfaceManager = 0;
	bShiftKeyDown = false;
	fSnapDistance = 10.0f;
	enable();
}

ProjectionEditor::~ProjectionEditor(){
	clearJoints();
	surfaceManager = 0;
	disable();
}

void ProjectionEditor::registerAppEvents(){
	ofAddListener(ofEvents().update, this, &ProjectionEditor::update);
	ofAddListener(ofEvents().messageEvent, this, &ProjectionEditor::gotMessage);
}

void ProjectionEditor::unregisterAppEvents(){
	ofRemoveListener(ofEvents().update, this, &ProjectionEditor::update);
	ofRemoveListener(ofEvents().messageEvent, this,
					 &ProjectionEditor::gotMessage);
}

void ProjectionEditor::registerMouseEvents(){
	ofAddListener(ofEvents().mouseDragged, this, &ProjectionEditor::mouseDragged);
}

void ProjectionEditor::unregisterMouseEvents(){
	ofRemoveListener(ofEvents().mouseDragged, this,
					 &ProjectionEditor::mouseDragged);
}

void ProjectionEditor::enable(){
	registerAppEvents();
	registerMouseEvents();
}

void ProjectionEditor::disable(){
	unregisterAppEvents();
	unregisterMouseEvents();
}

void ProjectionEditor::update(ofEventArgs & args){
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

void ProjectionEditor::draw(){
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

void ProjectionEditor::mouseDragged(ofMouseEventArgs & args){
	
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
			continue;          // Don't add vertices of selected surface
		}
		for(int j = 0; j < surface->getVertices().size(); j++){
			allVertices.push_back(&surface->getVertices()[j]);
		}
	}

	// Snap currently dragged joint to nearest vertex
	for(int i = 0; i < joints.size(); i++){
		if(joints[i]->isDragged()){
			// Snap it!
			for(int j = 0; j < allVertices.size(); j++){
				float distance = mousePosition.distance(*allVertices[j]);
				// cout << "distance: " << distance << endl;
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

void ProjectionEditor::gotMessage(ofMessage & msg){
	if(msg.message == "surfaceSelected"){
		// refresh gui
		clearJoints();
		createJoints();
	}
}

void ProjectionEditor::setSurfaceManager(SurfaceManager * newSurfaceManager){
	surfaceManager = newSurfaceManager;
}

void ProjectionEditor::clearJoints(){
	while(joints.size()){
		delete joints.back();
		joints.pop_back();
	}
}

void ProjectionEditor::createJoints(){
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

void ProjectionEditor::updateJoints(){
	if(surfaceManager->getSelectedSurface()){
		vector <ofVec3f> & vertices =
			surfaceManager->getSelectedSurface()->getVertices();
		for(int i = 0; i < vertices.size(); i++){
			joints[i]->position = ofVec2f(vertices[i].x, vertices[i].y);
		}
	}

}

void ProjectionEditor::unselectAllJoints(){
	for(int i = 0; i < joints.size(); i++){
		joints[i]->unselect();
	}
}

void ProjectionEditor::moveSelectedSurface(ofVec2f by){
	if(surfaceManager == 0){
		return;
	}
	if(surfaceManager->getSelectedSurface() == 0){
		return;
	}
	surfaceManager->getSelectedSurface()->moveBy(by);
	updateJoints();
}

void ProjectionEditor::stopDragJoints(){
	for(int i = 0; i < joints.size(); i++){
		joints[i]->stopDrag();
	}
}

void ProjectionEditor::setSnapDistance(float newSnapDistance){
	fSnapDistance = newSnapDistance;
}

CircleJoint * ProjectionEditor::hitTestJoints(ofVec2f pos){
	for(int i = 0; i < joints.size(); i++){
		if(joints[i]->hitTest(pos)){
			return joints[i];
		}
	}
	return 0;
}

vector <CircleJoint *> * ProjectionEditor::getJoints(){
	return &joints;
}

void ProjectionEditor::drawJoints(){
	for(int i = 0; i < joints.size(); i++){
		joints[i]->draw();
	}
}

} // namespace piMapper
} // namespace ofx