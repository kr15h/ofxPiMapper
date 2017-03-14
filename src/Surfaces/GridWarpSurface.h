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
		void moveBy(ofDefaultVec2 v);
	
		int getType();
		int getGridRows();
		int getGridCols();
		int setGridRows(int r);
		int setGridCols(int c);
	
		bool hitTest(ofDefaultVec2 p);
	
		ofPolyline getHitArea();
		ofPolyline getTextureHitArea();

		void setVertex(int index, ofDefaultVec3 v);
		void setVertices(vector<ofDefaultVec3> v);
		void setTexCoord(int index, ofDefaultVec2 t);
		void setTexCoords(vector<ofDefaultVec2> t);
		vector <ofDefaultVec3> & getVertices();
		vector <ofDefaultVec2> & getTexCoords();
	
		void createGridMesh();
	
		BaseSurface * clone();

	private:
		int _gridCols;
		int _gridRows;
};

} // namespace piMapper
} // namespace ofx