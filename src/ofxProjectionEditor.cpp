#include "ofxProjectionEditor.h"

ofxProjectionEditor::ofxProjectionEditor()
{
    surfaceManager = NULL;
}

ofxProjectionEditor::~ofxProjectionEditor()
{
    clearJoints();
    surfaceManager = NULL;
}

void ofxProjectionEditor::draw()
{
    if ( surfaceManager == NULL ) return;
    cout << "ofxProjectionEditor::draw()" << endl;
    if ( surfaceManager->getSelectedSurface() == NULL ) return;
    if ( joints.size() <= 0 ) createJoints();
    drawJoints();
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

bool ofxProjectionEditor::hitTestJoints(ofVec2f pos)
{
    for ( int i=0; i<joints.size(); i++ ) {
        if ( joints[i]->hitTest(pos) ){
            return true;
        }
    }
    return false;
}

void ofxProjectionEditor::drawJoints()
{
    cout << "draw joints" << endl;
    for ( int i=0; i<joints.size(); i++ ) {
        joints[i]->draw();
    }
}