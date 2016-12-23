#include "FboSource.h"

namespace ofx {
namespace piMapper {

FboSource::FboSource(const int width, const int height) :
	width_(width), 
	height_(height) 
{
	name = PIMAPPER_FBO_SOURCE_DEF_NAME;
	loadable = false;
	loaded = false;
	type = SourceType::SOURCE_TYPE_FBO;
}

FboSource::~FboSource()
{
	removeAppListeners();
	clear();
}

void FboSource::addAppListeners()
{
	ofLogNotice("FboSource") << "Adding app listeners";
	ofAddListener(ofEvents().update, this,
				  &FboSource::onAppUpdate, OF_EVENT_ORDER_BEFORE_APP);
	ofAddListener(ofEvents().exit, this,
				  &FboSource::onAppExit, OF_EVENT_ORDER_AFTER_APP);
}

void FboSource::removeAppListeners()
{
	ofLogNotice("FboSource") << "Removing app listeners";
	ofRemoveListener(ofEvents().update, this,
					 &FboSource::onAppUpdate, OF_EVENT_ORDER_BEFORE_APP);
	ofRemoveListener(ofEvents().exit, this,
					 &FboSource::onAppExit, OF_EVENT_ORDER_AFTER_APP);
}

void FboSource::onAppUpdate(ofEventArgs & args)
{
	if(!fbo_.isAllocated())
	{
		ofLogWarning("FboSource") << "FBO not allocated";
		return;
	}
	glitch_.setFx(OFXPOSTGLITCH_OUTLINE, true);
	
	update();
}

void FboSource::onAppExit(ofEventArgs & args){
	// exit();
}

void FboSource::setup(){
	ofLogNotice("FboSource") << "Setting up...";	
	fbo_.allocate(width_, height_);
	glitch_.setup(&fbo_);
	
	// Clear fbo_
	fbo_.begin();
	ofClear(0);
	fbo_.end();

	#if (OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR >= 9) || OF_VERSION_MAJOR > 0
		texture = &(fbo_.getTexture());
	#else
		texture = &(fbo_.getTextureReference());
	#endif
}

int FboSource::getWidth()
{
	if(fbo_.isAllocated())
		return fbo_.getWidth();

	return 0;
}

int FboSource::getHeight()
{
	if(fbo_.isAllocated())
		return fbo_.getHeight();

	return 0;
}

} // namespace piMapper
} // namespace ofx