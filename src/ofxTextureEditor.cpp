#include "ofxTextureEditor.h"

ofxTextureEditor::ofxTextureEditor()
{
    clear();
}

ofxTextureEditor::ofxTextureEditor(ofxBaseSurface* newSurface)
{
    setSurface(newSurface);
}

ofxTextureEditor::~ofxTextureEditor()
{
    clear();
}

void ofxTextureEditor::draw()
{
    if ( surface != NULL ) {
        surface->drawTexture(ofVec2f(0.0f,0.0f));
    }
}

void ofxTextureEditor::setSurface(ofxBaseSurface* newSurface)
{
    surface = newSurface;
}

void ofxTextureEditor::clear()
{
    surface = NULL;
}