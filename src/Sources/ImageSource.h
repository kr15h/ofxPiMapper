#pragma once

#include "BaseSource.h"

namespace ofx {
namespace piMapper {

class ImageSource : public BaseSource {

	public:
		ImageSource();
		~ImageSource();
		string & getPath();
		void loadImage(string & filePath);
		void clear();
	private:
		ofImage * image;

};

} // namespace piMapper
} // namespace ofx