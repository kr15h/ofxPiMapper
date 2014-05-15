#include "ofxTextureEditor.h"

ofxTextureEditor::ofxTextureEditor()
{
    clear();
    registerAppEvents();
}

ofxTextureEditor::~ofxTextureEditor()
{
    clear();
    unregisterAppEvents();
}

void ofxTextureEditor::registerAppEvents()
{
    ofAddListener(ofEvents().update, this, &ofxTextureEditor::update);
}

void ofxTextureEditor::unregisterAppEvents()
{
    ofRemoveListener(ofEvents().update, this, &ofxTextureEditor::update);
}

void ofxTextureEditor::update(ofEventArgs &args)
{
    if ( surface == NULL ) return;
    
    // update surface if one of the joints is being dragged
    ofVec2f textureSize = ofVec2f( surface->getTexture()->getWidth(), surface->getTexture()->getHeight() );
    for ( int i=0; i<joints.size(); i++ ) {
        if ( joints[i]->isDragged() ) {
            // update vertex to new location
            surface->setTexCoord(i, joints[i]->position / textureSize);
            break;
        }
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

ofxCircleJoint* ofxTextureEditor::hitTestJoints(ofVec2f pos)
{
    for ( int i=0; i<joints.size(); i++ ) {
        if ( joints[i]->hitTest(pos) ){
            return joints[i];
        }
    }
    return NULL;
}