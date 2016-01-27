#pragma once

#include "ofMain.h"
#include "BaseSurface.h"
#include "SurfaceType.h"
#include "HomographyHelper.h"

namespace ofx {
namespace piMapper {

class GridWarpSurface : public BaseSurface {
	public:
		GridWarpSurface();

		void draw();
		void moveBy(ofVec2f v);
	
		int getType();
	
		bool hitTest(ofVec2f p);
	
		ofPolyline getHitArea();
		ofPolyline getTextureHitArea();

		void setVertex(int index, ofVec2f p);
		void setVertices(vector<ofVec2f> v);
		vector <ofVec3f> & getVertices();


	private:
		int _gridCols;
		int _gridRows;
	
		void createGridMesh();
};

} // namespace piMapper
} // namespace ofx