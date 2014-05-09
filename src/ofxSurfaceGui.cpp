#include "ofxSurfaceGui.h"

ofxSurfaceGui::ofxSurfaceGui()
{
    jointCounter = 0;
}

ofxSurfaceGui::~ofxSurfaceGui()
{
    
}

void ofxSurfaceGui::setup(ofxTriangleSurface& surfaceForGui)
{
    surface = &surfaceForGui;
    addNumJoints(3);
}

void ofxSurfaceGui::addJoint()
{
    jointCounter++;
}

void ofxSurfaceGui::addNumJoints(int num)
{
    for ( int i=0; i<num; i++ ) {
        addJoint();
        joints[i].position = surface->getVertex(i);
    }
}