#include "ofxSurfaceGui.h"

ofxSurfaceGui::ofxSurfaceGui()
{
    surface = NULL;
    mode = NONE;
    bProjectionMappingJointSelected = false;
    bTextureMappingJointSelected = false;
    bTextureDragging = false;
    bProjectionDragging = false;
    bSelected = false;
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
    
    if (mode == PROJECTION_MAPPING) {
        for ( int i=0; i<projectionMappingJoints.size(); i++ ) {
            projectionMappingJoints[i].update();
        }
    } else if (mode == TEXTURE_MAPPING) {
        for ( int i=0; i<textureMappingJoints.size(); i++ ) {
            textureMappingJoints[i].update();
        }
    }
}

void ofxSurfaceGui::draw()
{
    if (surface == NULL) return;
    if (mode == NONE) return;
    
    // This has to be on bottom, so is drawn first
    if (bSelected && mode == TEXTURE_MAPPING) {
        ofPolyline line;
        for ( int i=0; i<textureMappingJoints.size(); i++ ) {
            line.addVertex( ofPoint(textureMappingJoints[i].position.x,
                                    textureMappingJoints[i].position.y) );
        }
        line.close();
        line.draw();
        
        for ( int i=0; i<textureMappingJoints.size(); i++ ) {
            textureMappingJoints[i].draw();
        }
    }
    
    // Draw line around projection surface always when selected
    if ( bSelected ) {
        ofPolyline line;
        for ( int i=0; i<projectionMappingJoints.size(); i++ ) {
            line.addVertex( ofPoint(projectionMappingJoints[i].position.x,
                                    projectionMappingJoints[i].position.y) );
        }
        line.close();
        line.draw();
    }
    
    // Draw projection surface joints
    if (bSelected && mode == PROJECTION_MAPPING) {
        for ( int i=0; i<projectionMappingJoints.size(); i++ ) {
            projectionMappingJoints[i].draw();
        }
    }
}

void ofxSurfaceGui::mousePressed(int x, int y, int button)
{
    if (surface == NULL) return;
    if (mode == NONE) return;
    if (!bSelected) return;
    
    if (mode == PROJECTION_MAPPING) {
        bProjectionMappingJointSelected = false;
        for ( int i=0; i<projectionMappingJoints.size(); i++ ) {
            projectionMappingJoints[i].selected = false;
            projectionMappingJoints[i].mousePressed(x, y, button);
            if ( !isProjectionMappingJointSelected() && projectionMappingJoints[i].hitTest(ofVec2f(x, y)) ) {
                projectionMappingJoints[i].selected = true;
                projectionMappingJoints[i].startDrag();
                bProjectionMappingJointSelected = true;
            }
        }
        
        if ( !bProjectionMappingJointSelected ) {
            // Check if we are hitting projection hitarea
            if ( projectionHitarea.inside(x, y) ) {
                clickPosition = ofVec2f(x, y);
                stopDrag();
                dragProjectionArea();
            }
        }
    } else if (mode == TEXTURE_MAPPING) {
        bTextureMappingJointSelected = false;
        for ( int i=0; i<textureMappingJoints.size(); i++ ) {
            textureMappingJoints[i].selected = false;
            textureMappingJoints[i].mousePressed(x, y, button);
            if ( !isTextureMappingJointSelected() && textureMappingJoints[i].hitTest(ofVec2f(x, y)) ) {
                textureMappingJoints[i].selected = true;
                textureMappingJoints[i].startDrag();
                bTextureMappingJointSelected = true;
            }
        }
        
        if ( !bTextureMappingJointSelected ) {
            // Check  if we are hitting the texture mapping hitarea
            if ( textureHitarea.inside(x, y) ) {
                clickPosition = ofVec2f(x, y);
                stopDrag();
                dragTextureArea();
            }
        }
    }
}

void ofxSurfaceGui::mouseReleased(int x, int y, int button)
{
    if (surface == NULL) return;
    stopDrag();
    if (mode == NONE) return;
    
    if (mode == PROJECTION_MAPPING) {
        for ( int i=0; i<projectionMappingJoints.size(); i++ ) {
            projectionMappingJoints[i].mouseReleased(x, y, button);
        }
    } else if (mode == TEXTURE_MAPPING) {
        for ( int i=0; i<textureMappingJoints.size(); i++ ) {
            textureMappingJoints[i].mouseReleased(x, y, button);
        }
    }
}

void ofxSurfaceGui::mouseDragged(int x, int y, int button)
{
    if (surface == NULL) return;
    if (mode == NONE) return;
    if (!bSelected) return;
    
    if (mode == PROJECTION_MAPPING) {
        if ( bProjectionDragging ) {
            ofVec2f curPos = ofVec2f(x, y);
            ofVec2f dist = curPos - clickPosition;
            for ( int i=0; i<projectionMappingJoints.size(); i++ ) {
                projectionMappingJoints[i].position += dist;
                surface->setVertex(i, projectionMappingJoints[i].position);
            }
            updateProjectionHitarea();
            clickPosition = curPos;
        } else {
            for ( int i=0; i<projectionMappingJoints.size(); i++ ) {
                projectionMappingJoints[i].mouseDragged(x, y, button);
                if ( projectionMappingJoints[i].isDragged() ) {
                    surface->setVertex(i, projectionMappingJoints[i].position);
                    updateProjectionHitarea();
                }
            } // for
        } // if ( bProjectionDragging
    } else if (mode == TEXTURE_MAPPING) {
        ofVec2f textureSize = ofVec2f( surface->getTexture()->getWidth(), surface->getTexture()->getHeight() );
        if ( bTextureDragging ) {
            ofVec2f curPos = ofVec2f(x, y);
            ofVec2f dist = curPos - clickPosition;
            for ( int i=0; i<textureMappingJoints.size(); i++ ) {
                textureMappingJoints[i].position += dist;
                surface->setTexCoord(i, textureMappingJoints[i].position/textureSize);
            }
            updateTextureHitarea();
            clickPosition = curPos;
        } else {
            for ( int i=0; i<textureMappingJoints.size(); i++ ) {
                textureMappingJoints[i].mouseDragged(x, y, button);
                if ( textureMappingJoints[i].isDragged() ) {
                    surface->setTexCoord(i, textureMappingJoints[i].position/textureSize);
                    updateTextureHitarea();
                }
            } // for
        } // if ( bTextureDragging
    } // if (mode
}

void ofxSurfaceGui::setMode(ofxSurfaceGui::editMode newMode)
{
    if (mode != NONE &&
        mode != PROJECTION_MAPPING &&
        mode != TEXTURE_MAPPING) {
        throw std::runtime_error("Trying to set invalid mode.");
    };
    
    mode = newMode;
}

void ofxSurfaceGui::select()
{
    bSelected = true;
}

void ofxSurfaceGui::unselect()
{
    bSelected = false;
}

bool ofxSurfaceGui::hitTest(float x, float y)
{
    if ( projectionAreaExists() ) {
        if ( projectionHitarea.inside(x, y) ) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool ofxSurfaceGui::isSelected()
{
    return bSelected;
}

ofxSurfaceGui::editMode ofxSurfaceGui::getMode()
{
    return mode;
}

void ofxSurfaceGui::addProjectionMappingJoint()
{
    projectionMappingJoints.push_back(ofxCircleJoint());
    projectionMappingJoints.back().position = surface->getVertex(projectionMappingJoints.size()-1);
    updateProjectionHitarea();
}

void ofxSurfaceGui::addNumProjectionMappingJoints(int num)
{
    for ( int i=0; i<num; i++ ) {
        addProjectionMappingJoint();
    }
}

void ofxSurfaceGui::addTextureMappingJoint()
{
    textureMappingJoints.push_back(ofxCircleJoint());
    ofVec2f textureSize = ofVec2f(surface->getTexture()->getWidth(), surface->getTexture()->getHeight());
    textureMappingJoints.back().position = surface->getTexCoord(textureMappingJoints.size()-1) * textureSize;
    updateTextureHitarea();
}

void ofxSurfaceGui::addNumTextureMappingJoints(int num)
{
    for ( int i=0; i<num; i++ ) {
        addTextureMappingJoint();
    }
}

void ofxSurfaceGui::updateTextureHitarea()
{
    textureHitarea.clear();
    for ( int i=0; i<textureMappingJoints.size(); i++ ) {
        textureHitarea.addVertex( ofPoint(textureMappingJoints[i].position.x,
                                          textureMappingJoints[i].position.y) );
    }
}

void ofxSurfaceGui::updateProjectionHitarea()
{
    projectionHitarea.clear();
    for ( int i=0; i<projectionMappingJoints.size(); i++ ) {
        projectionHitarea.addVertex( ofPoint(projectionMappingJoints[i].position.x,
                                             projectionMappingJoints[i].position.y) );
    }
}

void ofxSurfaceGui::dragTextureArea()
{
    bTextureDragging = true;
}

void ofxSurfaceGui::dragProjectionArea()
{
    bProjectionDragging = true;
}

void ofxSurfaceGui::stopDrag()
{
    bTextureDragging = false;
    bProjectionDragging = false;
}

bool ofxSurfaceGui::isProjectionMappingJointSelected()
{
    return bProjectionMappingJointSelected;
}

bool ofxSurfaceGui::isTextureMappingJointSelected()
{
    return bTextureMappingJointSelected;
}

bool ofxSurfaceGui::projectionAreaExists()
{
    if ( projectionHitarea.size() > 2 ) {
        return true;
    } else {
        return false;
    }
}