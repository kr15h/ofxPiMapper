#include "ImageSource.h"

namespace ofx {
namespace piMapper {

ImageSource::ImageSource(){
	//cout << "ImageSource" << endl;
	loadable = true;
	loaded = false;
	type = SourceType::SOURCE_TYPE_IMAGE;
}

ImageSource::~ImageSource(){}

void ImageSource::loadImage(string & filePath){
	path = filePath;
	//cout << "loading image: " << filePath << endl;
	setNameFromPath(filePath);
	//cout << "path: " << path << endl;
	image = new ofImage();
	#if (OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR >= 9) || OF_VERSION_MAJOR > 0
		if(!image->load(filePath)){
	#else
		if(!image->loadImage(filePath)){
	#endif
		ofLogWarning("ImageSource") << "Could not load image";
		//exit(EXIT_FAILURE);
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
	//path = "";
	//name = "";
	loaded = false;
}

} // namespace piMapper
} // namespace ofx