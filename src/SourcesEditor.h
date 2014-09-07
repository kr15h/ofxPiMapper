#pragma once

#include "ofGraphics.h"
#include "ofEvents.h"
#include "SurfaceManager.h"
#include "RadioList.h"

#define DEFAULT_IMAGES_DIR "sources/images/";

namespace ofx{
    namespace piMapper{
class SourcesEditor
{
public:
    SourcesEditor();
    ~SourcesEditor();
    
    void registerAppEvents();
    void unregisterAppEvents();
    
    void setup(ofEventArgs& args);
    void draw();
    void loadImage( string name, string path );
    void disable();
    void enable();
    void setSurfaceManager(SurfaceManager* newSurfaceManager);
    void selectImageSourceRadioButton(string name);
    
    int getLoadedTexCount();
    ofTexture* getTexture(int index);
    
private:
    SurfaceManager* surfaceManager;
    RadioList* gui;
    string defImgDir;
    void guiEvent(string &imageName);
    vector<ofImage*> images;
    vector<string> imageNames;
};

    }}