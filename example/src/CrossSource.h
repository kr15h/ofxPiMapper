#pragma once

#include "ofMain.h"
#include "FboSource.h"

class CrossSource : public ofx::piMapper::FboSource {
	public:
		CrossSource();

		void draw();
};