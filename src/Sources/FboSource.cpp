#include "FboSource.h"

namespace ofx {
namespace piMapper {

FboSource::FboSource() : fbo(0){
	name = PIMAPPER_FBO_SOURCE_DEF_NAME;
	loadable = false;
	loaded = false;
	type = SourceType::SOURCE_TYPE_FBO;
	ofAddListener(ofEvents().setup, this,
				  &FboSource::onAppSetup, OF_EVENT_ORDER_BEFORE_APP);
}

FboSource::~FboSource(){
	removeAppListeners();
	clear();
}

void FboSource::addAppListeners(){
	ofLogNotice("FboSource") << "Adding app listeners";
	ofAddListener(ofEvents().update, this,
				  &FboSource::onAppUpdate, OF_EVENT_ORDER_BEFORE_APP);
	ofAddListener(ofEvents().draw, this,
				  &FboSource::onAppDraw, OF_EVENT_ORDER_BEFORE_APP);
	ofAddListener(ofEvents().exit, this,
				  &FboSource::onAppExit, OF_EVENT_ORDER_AFTER_APP);
}

void FboSource::removeAppListeners(){
	ofLogNotice("FboSource") << "Removing app listeners";
	ofRemoveListener(ofEvents().update, this,
					 &FboSource::onAppUpdate, OF_EVENT_ORDER_BEFORE_APP);
	ofRemoveListener(ofEvents().draw, this,
					 &FboSource::onAppDraw, OF_EVENT_ORDER_BEFORE_APP);
	ofRemoveListener(ofEvents().exit, this,
					 &FboSource::onAppExit, OF_EVENT_ORDER_AFTER_APP);
}

void FboSource::onAppSetup(ofEventArgs & args){
	ofRemoveListener(ofEvents().setup, this,
					 &FboSource::onAppSetup, OF_EVENT_ORDER_BEFORE_APP);
	setup();

	// Check if FBO was allocated in user defined setup
	// If not, show warning and alocate to avoid panic
	if(!fbo->isAllocated()){
		ofLogWarning("FboSource::onAppSetup")
			<< "FBO not allocated, allocating with default values";
		allocate(PIMAPPER_FBO_SOURCE_DEF_WIDTH,
				 PIMAPPER_FBO_SOURCE_DEF_HEIGHT);
	}
}

void FboSource::onAppUpdate(ofEventArgs & args){
	if(fbo == 0 || !fbo->isAllocated()){
		ofLogWarning("FboSource") << "FBO not allocated";
		return;
	}
	update();
}

void FboSource::onAppDraw(ofEventArgs & args){
	if(fbo == 0 || !fbo->isAllocated()){
		ofLogWarning("FboSource") << "FBO not allocated";
		return;
	}
	fbo->begin();
	draw();
	fbo->end();
}

void FboSource::onAppExit(ofEventArgs & args){
	exit();
}

void FboSource::allocate(int width, int height){
	clear();
	fbo = new ofFbo();
	fbo->allocate(width, height);

	// Clear FBO
	fbo->begin();
	ofClear(0);
	fbo->end();
	
	#if (OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR >= 9) || OF_VERSION_MAJOR > 0
		texture = &(fbo->getTexture());
	#else
		texture = &(fbo->getTextureReference());
	#endif
}

void FboSource::clear(){
	texture = 0;
	if(fbo != 0){
		delete fbo;
		fbo = 0;
	}
}

int FboSource::getWidth(){
	if(fbo->isAllocated()){
		return fbo->getWidth();
	}else{
		return 0;
	}
}

int FboSource::getHeight(){
	if(fbo->isAllocated()){
		return fbo->getHeight();
	}else{
		return 0;
	}
}

} // namespace piMapper
} // namespace ofx