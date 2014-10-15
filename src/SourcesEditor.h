#pragma once

#include "ofGraphics.h"
#include "ofEvents.h"
#include "SurfaceManager.h"
#include "RadioList.h"
#include "MediaServer.h"

#define DEFAULT_IMAGES_DIR "sources/images/";

namespace ofx {
namespace piMapper {
class SourcesEditor {
 public:
  // Default contructor that initializes media server locally,
  // thus requiring to delete the media server from memory on deconstr
  SourcesEditor();
  
  // Alternative constructor that allows to assign external media server
  SourcesEditor(MediaServer* externalMediaServer);
  ~SourcesEditor();

  // Init handles variable initialization in all constructors
  void init();
  void registerAppEvents();
  void unregisterAppEvents();

  void setup(ofEventArgs& args);
  void draw();
  void loadImage(string name, string path);
  void disable();
  void enable();
  void setSurfaceManager(SurfaceManager* newSurfaceManager);
  void selectImageSourceRadioButton(string name);

  int getLoadedTexCount();
  ofTexture* getTexture(int index);

 private:
  MediaServer* mediaServer;
  bool isMediaServerExternal;
  SurfaceManager* surfaceManager;
  RadioList* gui;
  string defImgDir;
  void guiEvent(string& imageName);
  vector<ofImage*> images;
  vector<string> imageNames;
};
}
}