#include "ofxSurfaceGui.h"

ofxSurfaceGui::ofxSurfaceGui()
{
    surface = NULL;
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
    if (surface == NULL) return;
    
    for ( int i=0; i<joints.size(); i++ ) {
        joints[i].update();
    }
}

void ofxSurfaceGui::draw()
{
    if (surface == NULL) return;
    for ( int i=0; i<joints.size(); i++ ) {
        joints[i].draw();
    }
}

void ofxSurfaceGui::mousePressed(int x, int y, int button)
{
    if (surface == NULL) return;
    for ( int i=0; i<joints.size(); i++ ) {
        joints[i].mousePressed(x, y, button);
    }
}

void ofxSurfaceGui::mouseReleased(int x, int y, int button)
{
    if (surface == NULL) return;
    for ( int i=0; i<joints.size(); i++ ) {
        joints[i].mouseReleased(x, y, button);
    }
}

void ofxSurfaceGui::mouseDragged(int x, int y, int button)
{
    if (surface == NULL) return;
    for ( int i=0; i<joints.size(); i++ ) {
        joints[i].mouseDragged(x, y, button);
        if ( joints[i].isDragged() ) {
            surface->setVertex(i, joints[i].position);
        }
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