#include "FboSource.h"

namespace ofx {
namespace piMapper {

FboSource::FboSource(){
	fbo = 0;
	name = PIMAPPER_FBO_SOURCE_DEF_NAME;
	loadable = false;
	loaded = false;
	type = SourceType::SOURCE_TYPE_FBO;
	_disableDraw = false;
}

FboSource::~FboSource(){
	clear();
}

void FboSource::updateFbo(){
	if(fbo == 0 || !fbo->isAllocated()){
		ofLogWarning("FboSource") << "FBO not allocated";
		return;
	}
	update();
}

void FboSource::beginFbo(){
    if(fbo == 0 || !fbo->isAllocated()){
        ofLogWarning("FboSource") << "FBO not allocated";
        return;
    }
    fbo->begin();
}

void FboSource::endFbo(){
    if(fbo == 0 || !fbo->isAllocated()){
        ofLogWarning("FboSource") << "FBO not allocated";
        return;
    }
    fbo->end();
}

void FboSource::drawFbo(){
	if(fbo == 0 || !fbo->isAllocated()){
		ofLogWarning("FboSource") << "FBO not allocated";
		return;
	}
	
	if(_disableDraw){
		return;
	}
	
	fbo->begin();
	draw();
	fbo->end();
}

void FboSource::setDisableDraw(bool b){
	_disableDraw = b;
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
