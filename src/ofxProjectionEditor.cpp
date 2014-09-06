#include "ofxProjectionEditor.h"

ofxProjectionEditor::ofxProjectionEditor()
{
    surfaceManager = NULL;
    bShiftKeyDown = false;
    fSnapDistance = 10.0f;
    enable();
}

ofxProjectionEditor::~ofxProjectionEditor()
{
    clearJoints();
    surfaceManager = NULL;
    disable();
}

void ofxProjectionEditor::registerAppEvents()
{
    ofAddListener(ofEvents().update, this, &ofxProjectionEditor::update);
    ofAddListener(ofEvents().messageEvent, this, &ofxProjectionEditor::gotMessage);
}

void ofxProjectionEditor::unregisterAppEvents()
{
    ofRemoveListener(ofEvents().update, this, &ofxProjectionEditor::update);
    ofRemoveListener(ofEvents().messageEvent, this, &ofxProjectionEditor::gotMessage);
}

void ofxProjectionEditor::registerMouseEvents()
{
    ofAddListener(ofEvents().mouseDragged, this, &ofxProjectionEditor::mouseDragged);
}

void ofxProjectionEditor::unregisterMouseEvents()
{
    ofRemoveListener(ofEvents().mouseDragged, this, &ofxProjectionEditor::mouseDragged);
}

void ofxProjectionEditor::registerKeyEvents()
{
    ofAddListener(ofEvents().keyPressed, this, &ofxProjectionEditor::keyPressed);
    ofAddListener(ofEvents().keyReleased, this, &ofxProjectionEditor::keyReleased);
}

void ofxProjectionEditor::unregisterKeyEvents()
{
    ofRemoveListener(ofEvents().keyPressed, this, &ofxProjectionEditor::keyPressed);
    ofRemoveListener(ofEvents().keyReleased, this, &ofxProjectionEditor::keyReleased);
}

void ofxProjectionEditor::enable()
{
    registerAppEvents();
    registerMouseEvents();
    registerKeyEvents();
}

void ofxProjectionEditor::disable()
{
    unregisterAppEvents();
    unregisterMouseEvents();
    unregisterKeyEvents();
}

void ofxProjectionEditor::update(ofEventArgs &args)
{
    // update surface if one of the joints is being dragged
    for ( int i=0; i<joints.size(); i++ ) {
        if ( joints[i]->isDragged() || joints[i]->isSelected() ) {
            
            if ( surfaceManager->getSelectedSurface() != NULL ) {
                // update vertex to new location
                surfaceManager->getSelectedSurface()->setVertex(i, joints[i]->position);
            } else {
                // clear joints if there is no surface selected
                // as the remove selected surface in the surface manager
                // is not supposed to access joints here
                joints.clear();
            }
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
    ofVec2f mousePosition = ofVec2f(args.x, args.y);
    
    // Collect all vertices of the projection surfaces
    vector<ofVec3f*> allVertices;
    for ( int i=0; i<surfaceManager->size(); i++ ) {
        ofxBaseSurface* surface = surfaceManager->getSurface(i);
        if ( surface == surfaceManager->getSelectedSurface() ) {
            continue; // Don't add vertices of selected surface
        }
        for ( int j=0; j<surface->getVertices().size(); j++ ) {
            allVertices.push_back(&surface->getVertices()[j]);
        }
    }
    
    // Snap currently dragged joint to nearest vertex
    for ( int i=0; i<joints.size(); i++ ) {
        if ( joints[i]->isDragged() ) {
            // Snap it!
            for ( int j=0; j<allVertices.size(); j++ ) {
                float distance = mousePosition.distance(*allVertices[j]);
                //cout << "distance: " << distance << endl;
                if ( distance < fSnapDistance ) {
                    joints[i]->position = *allVertices[j];
                    ofVec2f clickDistance = joints[i]->position - ofVec2f(args.x, args.y);
                    joints[i]->setClickDistance(clickDistance);
                    break;
                }
            }
        }
    }
}

void ofxProjectionEditor::keyPressed(ofKeyEventArgs &args)
{
    int key = args.key;
    float moveStep;
    
    if (bShiftKeyDown) moveStep = 10.0f;
    else moveStep = 0.5f;
    
    switch (key) {
        case OF_KEY_LEFT: moveSelection(ofVec2f(-moveStep,0.0f)); break;
        case OF_KEY_RIGHT: moveSelection(ofVec2f(moveStep,0.0f)); break;
        case OF_KEY_UP: moveSelection(ofVec2f(0.0f,-moveStep)); break;
        case OF_KEY_DOWN: moveSelection(ofVec2f(0.0f,moveStep)); break;
        case OF_KEY_SHIFT: bShiftKeyDown = true; break;
    }
}

void ofxProjectionEditor::keyReleased(ofKeyEventArgs &args)
{
    int key = args.key;
    switch (key) {
        case OF_KEY_SHIFT: bShiftKeyDown = false; break;
    }
}

void ofxProjectionEditor::gotMessage(ofMessage& msg)
{
    if (msg.message == "surfaceSelected") {
        // refresh gui
        clearJoints();
        createJoints();
    }
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

void ofxProjectionEditor::unselectAllJoints()
{
    for ( int i=0; i<joints.size(); i++ ) {
        joints[i]->unselect();
    }
}

void ofxProjectionEditor::moveSelectedSurface(ofVec2f by)
{
    if ( surfaceManager == NULL ) return;
    if ( surfaceManager->getSelectedSurface() == NULL ) return;
    surfaceManager->getSelectedSurface()->moveBy(by);
    /*vector<ofVec3f>& vertices = surfaceManager->getSelectedSurface()->getVertices();
    for (int i=0; i<vertices.size(); i++) {
        vertices[i] += by;
    }*/
    updateJoints();
}

void ofxProjectionEditor::stopDragJoints()
{
    for (int i=0; i<joints.size(); i++){
        joints[i]->stopDrag();
    }
}

void ofxProjectionEditor::moveSelection(ofVec2f by)
{
    // check if joints selected
    bool bJointSelected = false;
    ofxBaseJoint* selectedJoint;
    for ( int i=0; i<joints.size(); i++ ) {
        if (joints[i]->isSelected()) {
            bJointSelected = true;
            selectedJoint = joints[i];
            break;
        }
    }
    
    if ( bJointSelected ) {
        selectedJoint->position += by;
    } else {
        moveSelectedSurface(by);
    }
}

void ofxProjectionEditor::setSnapDistance(float newSnapDistance)
{
    fSnapDistance = newSnapDistance;
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