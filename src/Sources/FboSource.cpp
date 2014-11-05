#include "FboSource.h"

namespace ofx {
  namespace piMapper {
    FboSource::FboSource() : fbo(NULL) {
      name = PIMAPPER_DEF_FBO_SOURCE_NAME;
      loadable = false;
      loaded = false;
      type = SourceType::SOURCE_TYPE_FBO;
      ofAddListener(ofEvents().setup, this, &FboSource::onAppSetup, OF_EVENT_ORDER_BEFORE_APP);
    }
    
    FboSource::~FboSource() {
      removeAppListeners();
      clear();
    }
    
    void FboSource::addAppListeners() {
      ofLogNotice("FboSource") << "Adding app listeners";
      ofAddListener(ofEvents().update, this, &FboSource::onAppUpdate, OF_EVENT_ORDER_BEFORE_APP);
      ofAddListener(ofEvents().draw, this, &FboSource::onAppDraw, OF_EVENT_ORDER_BEFORE_APP);
      ofAddListener(ofEvents().exit, this, &FboSource::onAppExit, OF_EVENT_ORDER_AFTER_APP);
    }
    
    void FboSource::removeAppListeners() {
      ofLogNotice("FboSource") << "Removing app listeners";
      ofRemoveListener(ofEvents().update, this, &FboSource::onAppUpdate, OF_EVENT_ORDER_BEFORE_APP);
      ofRemoveListener(ofEvents().draw, this, &FboSource::onAppDraw, OF_EVENT_ORDER_BEFORE_APP);
      ofRemoveListener(ofEvents().exit, this, &FboSource::onAppExit, OF_EVENT_ORDER_AFTER_APP);
    }
    
    void FboSource::onAppSetup(ofEventArgs &args) {
      ofRemoveListener(ofEvents().setup, this, &FboSource::onAppSetup, OF_EVENT_ORDER_BEFORE_APP);
      setup();
    }
    
    void FboSource::onAppUpdate(ofEventArgs &args) {
      if (fbo == NULL || !fbo->isAllocated()) {
        ofLogWarning("FboSource") << "FBO not allocated";
        return;
      }
      update();
    }
    
    void FboSource::onAppDraw(ofEventArgs &args) {
      if (fbo == NULL || !fbo->isAllocated()) {
        ofLogWarning("FboSource") << "FBO not allocated";
        return;
      }
      fbo->begin();
      draw();
      fbo->end();
    }
    
    void FboSource::onAppExit(ofEventArgs &args) {
      exit();
    }
    
    void FboSource::allocate(int width, int height) {
      clear();
      fbo = new ofFbo();
      fbo->allocate(width, height);
      
      // Clear FBO
      fbo->begin();
      ofClear(0);
      fbo->end();
      
      texture = &(fbo->getTextureReference());
    }
    
    void FboSource::clear() {
      texture = NULL;
      if (fbo != NULL) {
        delete fbo;
        fbo = NULL;
      }
    }
    
  } // namespace piMapper
} // namespace ofx