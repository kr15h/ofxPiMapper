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

		void setup();
		void draw();
		void moveBy(ofVec2f v);
	
		int getType();
		int getGridRows();
		int getGridCols();
		int setGridRows(int r);
		int setGridCols(int c);
	
		bool hitTest(ofVec2f p);
	
		ofPolyline getHitArea();
		ofPolyline getTextureHitArea();

		void setVertex(int index, ofVec2f p);
		void setVertices(vector<ofVec2f> v);
		void setVertices(vector<ofVec3f> v);
		void setTexCoord(int index, ofVec2f t);
		void setTexCoords(vector<ofVec2f> t);
		vector <ofVec3f> & getVertices();
		vector <ofVec2f> & getTexCoords();
	
		void createGridMesh();
	
		BaseSurface * clone();

	private:
		int _gridCols;
		int _gridRows;
};

} // namespace piMapper
} // namespace ofx