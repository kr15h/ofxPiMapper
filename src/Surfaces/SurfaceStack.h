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
	
		ofEvent <vector<ofVec3f>> verticesChangedEvent;
		ofEvent <ofVec3f> vertexChangedEvent;
	
		void onVerticesChanged(vector<ofVec3f> & vertices);
		void onVertexChanged(ofVec3f & vertex);
	
	private:
		vector<BaseSurface *> _surfaces;
};

} // namespace piMapper
} // namespace ofx