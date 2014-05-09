#include "ofxSurfaceGui.h"

ofxSurfaceGui::ofxSurfaceGui()
{
    
}

ofxSurfaceGui::~ofxSurfaceGui()
{
    
}

void ofxSurfaceGui::setup(ofxTriangleSurface& surfaceForGui)
{
    surface = &surfaceForGui;
    addNumJoints(3);
}

void ofxSurfaceGui::update()
{
    for ( int i=0; i<joints.size(); i++ ) {
        joints[i].update();
    }
}

void ofxSurfaceGui::draw()
{
    for ( int i=0; i<joints.size(); i++ ) {
        joints[i].draw();
    }
}

void ofxSurfaceGui::mousePressed(int x, int y, int button)
{
    for ( int i=0; i<joints.size(); i++ ) {
        joints[i].mousePressed(x, y, button);
    }
}

void ofxSurfaceGui::mouseReleased(int x, int y, int button)
{
    for ( int i=0; i<joints.size(); i++ ) {
        joints[i].mouseReleased(x, y, button);
    }
}

void ofxSurfaceGui::mouseDragged(int x, int y, int button)
{
    for ( int i=0; i<joints.size(); i++ ) {
        joints[i].mouseDragged(x, y, button);
    }
}

void ofxSurfaceGui::addJoint()
{
    joints.push_back(ofxCircleJoint());
}

void ofxSurfaceGui::addNumJoints(int num)
{
    for ( int i=0; i<num; i++ ) {
        addJoint();
        joints[i].position = surface->getVertex(i);
    }
}