#include "ofxProjectionEditor.h"

ofxProjectionEditor::ofxProjectionEditor()
{
    surfaceManager = NULL;
    registerAppEvents();
    registerMouseEvents();
}

ofxProjectionEditor::~ofxProjectionEditor()
{
    clearJoints();
    surfaceManager = NULL;
    unregisterAppEvents();
    unregisterMouseEvents();
}

void ofxProjectionEditor::registerAppEvents()
{
    ofAddListener(ofEvents().update, this, &ofxProjectionEditor::update);
}

void ofxProjectionEditor::unregisterAppEvents()
{
    ofRemoveListener(ofEvents().update, this, &ofxProjectionEditor::update);
}

void ofxProjectionEditor::registerMouseEvents()
{
    ofAddListener(ofEvents().mouseDragged, this, &ofxProjectionEditor::mouseDragged);
}

void ofxProjectionEditor::unregisterMouseEvents()
{
    ofRemoveListener(ofEvents().mouseDragged, this, &ofxProjectionEditor::mouseDragged);
}

void ofxProjectionEditor::update(ofEventArgs &args)
{
    // update surface if one of the joints is being dragged
    for ( int i=0; i<joints.size(); i++ ) {
        if ( joints[i]->isDragged() ) {
            // update vertex to new location
            surfaceManager->getSelectedSurface()->setVertex(i, joints[i]->position);
            break;
        }
    }
}

void ofxProjectionEditor::draw()
{
    if ( surfaceManager == NULL ) return;
    if ( surfaceManager->getSelectedSurface() == NULL ) return;
    if ( joints.size() <= 0 ) createJoints();
    drawJoints();
}

void ofxProjectionEditor::mouseDragged(ofMouseEventArgs &args)
{
    //
}

void ofxProjectionEditor::setSurfaceManager(ofxSurfaceManager *newSurfaceManager)
{
    surfaceManager = newSurfaceManager;
}

void ofxProjectionEditor::clearJoints()
{
    while ( joints.size() ) {
        delete joints.back();
        joints.pop_back();
    }
}

void ofxProjectionEditor::createJoints()
{
    if ( surfaceManager == NULL ) return;
    clearJoints();
    
    if ( surfaceManager->getSelectedSurface() == NULL ) {
        ofLog(OF_LOG_WARNING, "Trying to create joints while no surface selected.");
        return;
    }
    
    vector<ofVec3f>& vertices = surfaceManager->getSelectedSurface()->getVertices();
    
    for ( int i=0; i<vertices.size(); i++ ) {
        joints.push_back( new ofxCircleJoint() );
        joints.back()->position = ofVec2f(vertices[i].x, vertices[i].y);
    }
}

void ofxProjectionEditor::updateJoints()
{
    vector<ofVec3f>& vertices = surfaceManager->getSelectedSurface()->getVertices();
    for ( int i=0; i<vertices.size(); i++ ) {
        joints[i]->position = ofVec2f(vertices[i].x, vertices[i].y);
    }
}

void ofxProjectionEditor::moveSelectedSurface(ofVec2f by)
{
    if ( surfaceManager == NULL ) return;
    if ( surfaceManager->getSelectedSurface() == NULL ) return;
    vector<ofVec3f>& vertices = surfaceManager->getSelectedSurface()->getVertices();
    for (int i=0; i<vertices.size(); i++) {
        vertices[i] += by;
    }
    updateJoints();
}

void ofxProjectionEditor::stopDragJoints()
{
    for (int i=0; i<joints.size(); i++){
        joints[i]->stopDrag();
    }
}

ofxCircleJoint* ofxProjectionEditor::hitTestJoints(ofVec2f pos)
{
    for ( int i=0; i<joints.size(); i++ ) {
        if ( joints[i]->hitTest(pos) ){
            return joints[i];
        }
    }
    return NULL;
}

void ofxProjectionEditor::drawJoints()
{
    for ( int i=0; i<joints.size(); i++ ) {
        joints[i]->draw();
    }
}