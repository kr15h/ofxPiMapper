#pragma once

#include "ofMain.h"
#include "BaseSurface.h"
#include "SurfaceType.h"
#include "HomographyHelper.h"
#include "Vec2.h"

namespace ofx {
namespace piMapper {

class GridWarpSurface : public BaseSurface {
	public:
		GridWarpSurface();

		void setup();
		void draw();
		void moveBy(Vec2 v);
	
		int getType();
		int getGridRows();
		int getGridCols();
		int setGridRows(int r);
		int setGridCols(int c);
	
		bool hitTest(Vec2 p);
	
		ofPolyline getHitArea();
		ofPolyline getTextureHitArea();

		void setVertex(int index, Vec2 p);
		void setVertices(vector<Vec2> v);
		void setVertices(vector<ofVec3f> v);
		void setTexCoord(int index, Vec2 t);
		void setTexCoords(vector<Vec2> t);
		vector <ofVec3f> & getVertices();
		vector <Vec2> & getTexCoords();
	
		void createGridMesh();
	
		BaseSurface * clone();

	private:
		int _gridCols;
		int _gridRows;
	
		vector<Vec2> _texCoords;
};

} // namespace piMapper
} // namespace ofx
