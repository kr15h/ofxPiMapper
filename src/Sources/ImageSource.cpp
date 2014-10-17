#include "ImageSource.h"

namespace ofx {
  namespace piMapper {
    ImageSource::ImageSource() {
      //cout << "ImageSource" << endl;
      loadable = true;
      loaded = false;
      type = SourceType::SOURCE_TYPE_IMAGE;
    }
    
    ImageSource::~ImageSource() {
      clear();
    }
    
    void ImageSource::loadImage(std::string& filePath) {
      path = filePath;
      cout << "loading image: " << filePath << endl;
      setNameFromPath(filePath);
      cout << "path: " << path << endl;
      image = new ofImage();
      if (!image->loadImage(filePath)) {
        ofLogFatalError("ImageSource") << "Could not load image";
        std::exit(EXIT_FAILURE);
      }
      texture = &image->getTextureReference();
      loaded = true;
    }
    
    void ImageSource::clear() {
      texture = NULL;
      image->clear();
      delete image;
      image = NULL;
      path = "";
      name = "";
      loaded = false;
    }
    
  }
}