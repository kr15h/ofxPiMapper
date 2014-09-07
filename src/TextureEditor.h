#pragma once

#include "ofEvents.h"

#include "BaseSurface.h"
#include "CircleJoint.h"


namespace ofx{
    namespace piMapper{
class TextureEditor
{
public:
    TextureEditor();
    ~TextureEditor();
    
    void registerAppEvents();
    void unregisterAppEvents();
    void registerKeyEvents();
    void unregisterKeyEvents();
    void enable();
    void disable();
    
    void update(ofEventArgs& args);
    void keyPressed(ofKeyEventArgs& args);
    void keyReleased(ofKeyEventArgs& args);
    void draw();
    void drawJoints();
    void setSurface(BaseSurface* newSurface);
    void clear();
    void createJoints();
    void clearJoints();
    void unselectAllJoints();
    void moveTexCoords(ofVec2f by);
    void stopDragJoints();
    void moveSelection(ofVec2f by);
    CircleJoint* hitTestJoints(ofVec2f pos);
    
private:
    BaseSurface* surface;
    vector<CircleJoint*> joints;
    bool bShiftKeyDown;
};

    }}