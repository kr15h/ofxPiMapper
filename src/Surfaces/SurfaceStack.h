#pragma once

#include "ofMain.h"
#include "BaseSurface.h"

namespace ofx {
namespace piMapper {

// One can imagine this as a layers panel in an image editor
class SurfaceStack {
	public:
		SurfaceStack();

		void push_back(BaseSurface * s);
		void pop_back();
		void erase(int i);
		void swap(int a, int b);
		void draw();
	
		int size();

		BaseSurface * operator[](int i);
		BaseSurface * back();
	
	private:
		vector<BaseSurface *> _surfaces;
};

} // namespace piMapper
} // namespace ofx