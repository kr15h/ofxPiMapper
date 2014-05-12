#include "ofxTextureEditor.h"

ofxTextureEditor::ofxTextureEditor()
{
    clear();
}

ofxTextureEditor::~ofxTextureEditor()
{
    clear();
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