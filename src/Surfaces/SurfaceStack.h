#pragma once

#include "ofMain.h"
#include "BaseSurface.h"

namespace ofx {
namespace piMapper {

/* TODO: Do not use singleton here. 
 * For presets we need multiple instances of surface stacks.
 */

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