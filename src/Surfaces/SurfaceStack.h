#pragma once

#include "ofMain.h"
#include "BaseSurface.h"

namespace ofx {
namespace piMapper {

// One can imagine this as a layers panel in an image editor.
// TODO: Make it singleton for easy access from commands.
// And refactor rest of the code to use it this way.
class SurfaceStack {
	public:
		static SurfaceStack * instance();
	
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
	
		ofEvent <vector<ofVec3f>> verticesChangedEvent;
		ofEvent <int> vertexChangedEvent;
	
		void onVerticesChanged(vector<ofVec3f> & vertices);
		void onVertexChanged(int & i);
	
		vector<BaseSurface *> & getSurfaces(){ return _surfaces; };
	
	private:
		SurfaceStack(){}
	
		static SurfaceStack * _instance;
	
		vector<BaseSurface *> _surfaces;
};

} // namespace piMapper
} // namespace ofx