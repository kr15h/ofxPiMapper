#pragma once

#include "BaseSource.h"

namespace ofx {
namespace piMapper {

class ImageSource : public BaseSource {

	public:
		ImageSource();
		~ImageSource();
		std::string & getPath();
		void loadImage(std::string & filePath);
		void clear();
	private:
		ofImage * image;

};

} // namespace piMapper
} // namespace ofx