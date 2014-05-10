#include "ofxSurfaceGui.h"

ofxSurfaceGui::ofxSurfaceGui()
{
    surface = NULL;
    mode = PROJECTION_MAPPING;
}

ofxSurfaceGui::~ofxSurfaceGui()
{
    
}

void ofxSurfaceGui::setup(ofxTriangleSurface& surfaceForGui)
{
    surface = &surfaceForGui;
    addNumProjectionMappingJoints(3);
    addNumTextureMappingJoints(3);
}

void ofxSurfaceGui::update()
{
    if (surface == NULL) return;
    if (mode == NONE) return;
    
    for ( int i=0; i<projectionMappingJoints.size(); i++ ) {
        projectionMappingJoints[i].update();
    }
}

void ofxSurfaceGui::draw()
{
    if (surface == NULL) return;
    if (mode == NONE) return;
    
    for ( int i=0; i<projectionMappingJoints.size(); i++ ) {
        projectionMappingJoints[i].draw();
    }
}

void ofxSurfaceGui::mousePressed(int x, int y, int button)
{
    if (surface == NULL) return;
    if (mode == NONE) return;
    
    for ( int i=0; i<projectionMappingJoints.size(); i++ ) {
        projectionMappingJoints[i].mousePressed(x, y, button);
    }
}

void ofxSurfaceGui::mouseReleased(int x, int y, int button)
{
    if (surface == NULL) return;
    if (mode == NONE) return;
    
    for ( int i=0; i<projectionMappingJoints.size(); i++ ) {
        projectionMappingJoints[i].mouseReleased(x, y, button);
    }
}

void ofxSurfaceGui::mouseDragged(int x, int y, int button)
{
    if (surface == NULL) return;
    if (mode == NONE) return;
    
    for ( int i=0; i<projectionMappingJoints.size(); i++ ) {
        projectionMappingJoints[i].mouseDragged(x, y, button);
        if ( projectionMappingJoints[i].isDragged() ) {
            surface->setVertex(i, projectionMappingJoints[i].position);
        }
    }
}

void ofxSurfaceGui::setMode(ofxSurfaceGui::editMode newMode)
{
    if (mode != NONE ||
        mode != PROJECTION_MAPPING ||
        mode != TEXTURE_MAPPING) {
        throw std::runtime_error("Trying to set invalid mode.");
    };
}

ofxSurfaceGui::editMode ofxSurfaceGui::getMode()
{
    return mode;
}

void ofxSurfaceGui::addProjectionMappingJoint()
{
    projectionMappingJoints.push_back(ofxCircleJoint());
    projectionMappingJoints.back().position = surface->getVertex(projectionMappingJoints.size()-1);
}

void ofxSurfaceGui::addNumProjectionMappingJoints(int num)
{
    for ( int i=0; i<num; i++ ) {
        addProjectionMappingJoint();
    }
}

void ofxSurfaceGui::addTextureMappingJoint()
{
    textureMappingJoings.push_back(ofxCircleJoint());
    //textureMappingJoings.back().position = surface->getTex
}

void ofxSurfaceGui::addNumTextureMappingJoints(int num)
{
    for ( int i=0; i<num; i++ ) {
        addTextureMappingJoint();
    }
}