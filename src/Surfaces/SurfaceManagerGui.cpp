#include "SurfaceManagerGui.h"

namespace ofx {
    namespace piMapper {
        SurfaceManagerGui::SurfaceManagerGui() {
            surfaceManager = NULL;
            guiMode = GuiMode::NONE;
            bDrag = false;
            registerMouseEvents();
            ofHideCursor();
            _cmdManager = 0;
        }
        
        SurfaceManagerGui::~SurfaceManagerGui() {
            unregisterMouseEvents();
            surfaceManager = NULL;
            _cmdManager = 0;
        }
        
        void SurfaceManagerGui::registerMouseEvents() {
            ofAddListener(ofEvents().mousePressed, this,
                          &SurfaceManagerGui::mousePressed);
            ofAddListener(ofEvents().mouseReleased, this,
                          &SurfaceManagerGui::mouseReleased);
            ofAddListener(ofEvents().mouseDragged, this,
                          &SurfaceManagerGui::mouseDragged);
        }
        
        void SurfaceManagerGui::unregisterMouseEvents() {
            ofRemoveListener(ofEvents().mousePressed, this,
                             &SurfaceManagerGui::mousePressed);
            ofRemoveListener(ofEvents().mouseReleased, this,
                             &SurfaceManagerGui::mouseReleased);
            ofRemoveListener(ofEvents().mouseDragged, this,
                             &SurfaceManagerGui::mouseDragged);
        }
        
        void SurfaceManagerGui::draw() {
            if (surfaceManager == NULL) return;
            
            if (guiMode == GuiMode::NONE) {
                surfaceManager->draw();
            } else if (guiMode == GuiMode::TEXTURE_MAPPING) {
                // draw the texture of the selected surface
                if (surfaceManager->getSelectedSurface() != NULL) {
                    surfaceManager->getSelectedSurface()->drawTexture(ofVec2f(0, 0));
                }
                
                // draw surfaces with opacity
                ofPushStyle();
                ofSetColor(255, 255, 255, 200);
                surfaceManager->draw();
                ofPopStyle();
                
                // highlight selected surface
                drawSelectedSurfaceHighlight();
                
                // hilight selected surface texture
                drawSelectedSurfaceTextureHighlight();
                
                // draw texture editing GUI on top
                textureEditor.draw();
                
            } else if (guiMode == GuiMode::PROJECTION_MAPPING) {
                // draw projection surfaces first
                surfaceManager->draw();
                
                // highlight selected surface
                drawSelectedSurfaceHighlight();
                
                // draw projection mapping editing gui
                projectionEditor.draw();
                
            } else if (guiMode == GuiMode::SOURCE_SELECTION) {
                // draw projection surfaces first
                surfaceManager->draw();
                
                // highlight selected surface
                drawSelectedSurfaceHighlight();
                
                sourcesEditor.draw();
            }
        }
        
        void SurfaceManagerGui::mousePressed(ofMouseEventArgs& args) {
            if (guiMode == GuiMode::NONE) {
                return;
            } else if (guiMode == GuiMode::TEXTURE_MAPPING) {
                bool bSurfaceSelected = false;
                CircleJoint* hitJoint =
                    textureEditor.hitTestJoints(ofVec2f(args.x, args.y));
                if (hitJoint != NULL) {
                    textureEditor.unselectAllJoints();
    
                    hitJoint->select();
                    hitJoint->startDrag();
                    bSurfaceSelected = true;
                    
                    int jointIndex = -1;
                    for (auto i = 0; i < textureEditor.getJoints().size(); i++) {
                        if (textureEditor.getJoints()[i] == hitJoint) {
                            jointIndex = i;
                            break;
                        }
                    }
                    
                    if (jointIndex != -1) {
                        _cmdManager->exec(new MvTexCoordCmd(jointIndex, &textureEditor));
                    }
                    
                } else {
                    textureEditor.unselectAllJoints();
                }
                
                if (surfaceManager->getSelectedSurface() != NULL && !bSurfaceSelected) {
                    // hittest texture area to see if we are hitting the texture surface
                    if (surfaceManager->getSelectedSurface()->getTextureHitArea().inside(
                        args.x, args.y)) {
                        
                        // TODO: move these to a separate routine
                        clickPosition = ofVec2f(args.x, args.y);
                        startDrag();
                        
                        _cmdManager->exec(new MvAllTexCoordsCmd(
                            surfaceManager->getSelectedSurface(),
                            &textureEditor));
                        
                    }
                }
                
            } else if (guiMode == GuiMode::PROJECTION_MAPPING) {
                bool bSurfaceSelected = false;
                
                CircleJoint* hitJoint =
                    projectionEditor.hitTestJoints(ofVec2f(args.x, args.y));
                if (hitJoint != NULL) {
                    projectionEditor.unselectAllJoints();
                    hitJoint->select();
                    hitJoint->startDrag();
                    int jointVertIndex = 0;
                    for (auto i = 0; i < projectionEditor.getJoints()->size(); i++) {
                        if ((*projectionEditor.getJoints())[i] == hitJoint) {
                            jointVertIndex = i;
                            break;
                        }
                    }
                    _cmdManager->exec(new MvSurfaceVertCmd(
                        jointVertIndex,
                        surfaceManager->getSelectedSurface(),
                        &projectionEditor));
                    bSurfaceSelected = true;
                }
                
                // attempt to select surface, loop from end to beginning
                if (!bSurfaceSelected) {
                    for (int i = surfaceManager->size() - 1; i >= 0; i--) {
                        if (surfaceManager->getSurface(i)->hitTest(ofVec2f(args.x, args.y))) {
                            
                            // Do not repeat this command if attempting to select an
                            // already selected surface.
                            if (surfaceManager->getSelectedSurface() != surfaceManager->getSurface(i)){
                                _cmdManager->exec(new SelSurfaceCmd(
                                    surfaceManager,
                                    surfaceManager->getSurface(i),
                                    &projectionEditor));
                            }
                            
                            bSurfaceSelected = true;
                            break;
                        }
                    }
                }
                
                if (bSurfaceSelected && hitJoint == NULL) {
                    
                    // if not hitting the joints, start drag only if
                    // we have a selected surface
                    clickPosition = ofVec2f(args.x, args.y);
                    startDrag();
                    
                    _cmdManager->exec(
                        new MvSurfaceCmd(
                            surfaceManager->getSelectedSurface(),
                            &projectionEditor));
                }
                
                if (!bSurfaceSelected) {
                    // unselect if no surface selected
                    projectionEditor.clearJoints();
                    surfaceManager->deselectSurface();
                }
            } else if (guiMode == GuiMode::SOURCE_SELECTION) {
            }
        }
        
        void SurfaceManagerGui::mouseReleased(ofMouseEventArgs& args) {
            stopDrag();
            projectionEditor.stopDragJoints();
            textureEditor.stopDragJoints();
            
            // Check if surface has moved
            if (surfaceManager->getSelectedSurface()){
                if (!surfaceManager->getSelectedSurface()->getMoved()) {
                    _cmdManager->undo();
                }
            }
            
        }
        
        void SurfaceManagerGui::mouseDragged(ofMouseEventArgs& args) {
            if (bDrag) {
                ofVec2f mousePosition = ofVec2f(args.x, args.y);
                ofVec2f distance = mousePosition - clickPosition;
                
                if (guiMode == GuiMode::PROJECTION_MAPPING) {
                    // add this distance to all vertices in surface
                    projectionEditor.moveSelectedSurface(distance);
                } else if (guiMode == GuiMode::TEXTURE_MAPPING) {
                    textureEditor.moveTexCoords(distance);
                }
                clickPosition = mousePosition;
            }
        }
        
        void SurfaceManagerGui::setSurfaceManager(SurfaceManager* newSurfaceManager) {
            surfaceManager = newSurfaceManager;
            projectionEditor.setSurfaceManager(surfaceManager);
            sourcesEditor.setSurfaceManager(surfaceManager);
        }
        
        // Set external media server so we can access it from wherever we need
        void SurfaceManagerGui::setMediaServer(MediaServer* newMediaServer) {
            mediaServer = newMediaServer;
            // Set the media server of the sources editor here
            sourcesEditor.setMediaServer(mediaServer);
        }
        
        void SurfaceManagerGui::setCmdManager(CmdManager * cmdManager){
            _cmdManager = cmdManager;
            sourcesEditor.setCmdManager(_cmdManager);
        }
        
        void SurfaceManagerGui::setMode(int newGuiMode) {
            if (newGuiMode != GuiMode::NONE && newGuiMode != GuiMode::TEXTURE_MAPPING &&
                newGuiMode != GuiMode::PROJECTION_MAPPING &&
                newGuiMode != GuiMode::SOURCE_SELECTION) {
                throw std::runtime_error("Trying to set invalid mode.");
            }
            
            if (newGuiMode == GuiMode::NONE) {
                ofHideCursor();
            } else {
                ofShowCursor();
            }
            
            guiMode = newGuiMode;
            
            if (guiMode == GuiMode::SOURCE_SELECTION) {
                sourcesEditor.enable();
                //string sourceName = surfaceManager->getSelectedSurfaceSourceName();
                //sourcesEditor.selectImageSourceRadioButton(sourceName);
            } else {
                sourcesEditor.disable();
            }
            
            if (guiMode == GuiMode::TEXTURE_MAPPING) {
                textureEditor.enable();
                // refresh texture editor surface reference
                textureEditor.setSurface(surfaceManager->getSelectedSurface());
            } else {
                textureEditor.disable();
            }
            
            if (guiMode == GuiMode::PROJECTION_MAPPING) {
                projectionEditor.enable();
            } else {
                projectionEditor.disable();
            }
        }
        
        int SurfaceManagerGui::getMode(){
            return guiMode;
        }
        
        void SurfaceManagerGui::drawSelectedSurfaceHighlight() {
            if (surfaceManager->getSelectedSurface() == NULL) return;
            ofPolyline line = surfaceManager->getSelectedSurface()->getHitArea();
            ofPushStyle();
            ofSetLineWidth(1);
            ofSetColor(255, 255, 255, 255);
            line.draw();
            ofPopStyle();
        }
        
        void SurfaceManagerGui::drawSelectedSurfaceTextureHighlight() {
            if (surfaceManager->getSelectedSurface() == NULL) return;
            ofPolyline line = surfaceManager->getSelectedSurface()->getTextureHitArea();
            ofPushStyle();
            ofSetLineWidth(1);
            ofSetColor(255, 255, 0, 255);
            line.draw();
            ofPopStyle();
        }
        
        void SurfaceManagerGui::startDrag() { bDrag = true; }
        
        void SurfaceManagerGui::stopDrag() { bDrag = false; }
    }
}