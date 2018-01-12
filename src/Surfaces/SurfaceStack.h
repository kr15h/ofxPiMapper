#pragma once

#include "ofMain.h"
#include "BaseSurface.h"

namespace ofx {
namespace piMapper {

class SurfaceStack {
	public:
		void push_back(BaseSurface * s);
		void pop_back();
		void erase(int i);
		void swap(int a, int b);
		void draw();
		void clear();
	
		int size();

		BaseSurface * operator[](int i);
		BaseSurface * at(int i);
		BaseSurface * back();
	
		ofEvent <std::vector<Vec3>> verticesChangedEvent;
		ofEvent <int> vertexChangedEvent;
	
		void onVerticesChanged(std::vector<Vec3> & vertices);
		void onVertexChanged(int & i);
	
		std::vector<BaseSurface *> & getSurfaces(){ return _surfaces; };
	
		SurfaceStack * clone();
	
	private:
		std::vector<BaseSurface *> _surfaces;
};

} // namespace piMapper
} // namespace ofx
