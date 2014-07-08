#include "ofxTextureEditor.h"

ofxTextureEditor::ofxTextureEditor()
{
    clear();
    enable();
}

ofxTextureEditor::~ofxTextureEditor()
{
    clear();
    disable();
}

void ofxTextureEditor::registerAppEvents()
{
    ofAddListener(ofEvents().update, this, &ofxTextureEditor::update);
}

void ofxTextureEditor::unregisterAppEvents()
{
    ofRemoveListener(ofEvents().update, this, &ofxTextureEditor::update);
}

void ofxTextureEditor::registerKeyEvents()
{
    ofAddListener(ofEvents().keyPressed, this, &ofxTextureEditor::keyPressed);
    ofAddListener(ofEvents().keyReleased, this, &ofxTextureEditor::keyReleased);
}

void ofxTextureEditor::unregisterKeyEvents()
{
    ofRemoveListener(ofEvents().keyPressed, this, &ofxTextureEditor::keyPressed);
    ofRemoveListener(ofEvents().keyReleased, this, &ofxTextureEditor::keyReleased);
}

void ofxTextureEditor::enable()
{
    registerAppEvents();
    registerKeyEvents();
    bShiftKeyDown = false;
}

void ofxTextureEditor::disable()
{
    unregisterAppEvents();
    unregisterKeyEvents();
}

void ofxTextureEditor::update(ofEventArgs &args)
{
    if ( surface == NULL ) return;
    
    // update surface if one of the joints is being dragged
    ofVec2f textureSize = ofVec2f( surface->getTexture()->getWidth(), surface->getTexture()->getHeight() );
    for ( int i=0; i<joints.size(); i++ ) {
        if ( joints[i]->isDragged() || joints[i]->isSelected() ) {
            // update vertex to new location
            surface->setTexCoord(i, joints[i]->position / textureSize);
            break;
        }
    }
}

void ofxTextureEditor::keyPressed(ofKeyEventArgs &args)
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

void ofxTextureEditor::keyReleased(ofKeyEventArgs &args)
{
    int key = args.key;
    switch (key) {
        case OF_KEY_SHIFT: bShiftKeyDown = false; break;
    }
}


void ofxTextureEditor::draw()
{
    if (surface == NULL) return;
    
    drawJoints();
}

void ofxTextureEditor::drawJoints()
{
    for ( int i=0; i<joints.size(); i++ ) {
        joints[i]->draw();
    }
}

void ofxTextureEditor::setSurface(ofxBaseSurface* newSurface)
{
    surface = newSurface;
    createJoints();
}

void ofxTextureEditor::clear()
{
    surface = NULL;
    clearJoints();
}

void ofxTextureEditor::createJoints()
{
    if ( surface == NULL ) return;
    clearJoints();
    vector<ofVec2f>& texCoords = surface->getTexCoords();
    ofVec2f textureSize = ofVec2f(surface->getTexture()->getWidth(), surface->getTexture()->getHeight());
    
    for ( int i=0; i<texCoords.size(); i++ ) {
        joints.push_back(new ofxCircleJoint());
        joints.back()->position = texCoords[i] * textureSize;
    }
}

void ofxTextureEditor::clearJoints()
{
    while ( joints.size() ) {
        delete joints.back();
        joints.pop_back();
    }
}

void ofxTextureEditor::unselectAllJoints()
{
    for ( int i=0; i<joints.size(); i++ ) {
        joints[i]->unselect();
    }
}

void ofxTextureEditor::moveTexCoords(ofVec2f by)
{
    if ( surface == NULL ) return;
    vector<ofVec2f>& texCoords = surface->getTexCoords();
    ofVec2f textureSize = ofVec2f( surface->getTexture()->getWidth(), surface->getTexture()->getHeight() );
    for (int i=0; i<texCoords.size(); i++) {
        joints[i]->position += by;
        texCoords[i] = joints[i]->position / textureSize;
    }
}

void ofxTextureEditor::stopDragJoints()
{
    for (int i=0; i<joints.size(); i++){
        joints[i]->stopDrag();
    }
}

void ofxTextureEditor::moveSelection(ofVec2f by)
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
        moveTexCoords(by);
    }
}

ofxCircleJoint* ofxTextureEditor::hitTestJoints(ofVec2f pos)
{
    for ( int i=0; i<joints.size(); i++ ) {
        if ( joints[i]->hitTest(pos) ){
            return joints[i];
        }
    }
    return NULL;
}