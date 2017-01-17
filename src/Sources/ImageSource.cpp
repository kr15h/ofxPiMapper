#include "ImageSource.h"

namespace ofx {
namespace piMapper {

ImageSource::ImageSource(){
	loadable = true;
	loaded = false;
	type = SourceType::SOURCE_TYPE_IMAGE;
}

ImageSource::~ImageSource(){}

void ImageSource::loadImage(string & filePath){
	path = filePath;
	setNameFromPath(filePath);
	image = new ofImage();
	#if (OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR >= 9) || OF_VERSION_MAJOR > 0
		if(!image->load(filePath)){
	#else
		if(!image->loadImage(filePath)){
	#endif
		ofLogWarning("ImageSource") << "Could not load image";
	}
	#if (OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR >= 9) || OF_VERSION_MAJOR > 0
		texture = &image->getTexture();
	#else
		texture = &image->getTextureReference();
	#endif
	loaded = true;
}

void ImageSource::clear(){
	texture = 0;
	image->clear();
	delete image;
	image = 0;
	loaded = false;
}

} // namespace piMapper
} // namespace ofx