#pragma once

#include "ofMain.h"
#include "BaseSurface.h"
#include "SurfaceType.h"
#include "HomographyHelper.h"
#include "Vec2.h"
#include "Vec3.h"

namespace ofx {
namespace piMapper {

class GridWarpSurface : public BaseSurface {
	public:
		GridWarpSurface();

		void setup(){};
		void draw();
		void moveBy(Vec3 v);
        void fullScreen();
	
		int getType();
		int getGridRows();
		int getGridCols();
		int setGridRows(int r);
		int setGridCols(int c);
	
		bool hitTest(Vec2 p);
	
		ofPolyline getHitArea();
		ofPolyline getTextureHitArea();

		void setVertex(int index, Vec3 p);
		void setVertices(std::vector<Vec3> v);
		void setTexCoord(int index, Vec2 t);
		void setTexCoords(std::vector<Vec2> t);
		std::vector<Vec3> getVertices();
		std::vector<Vec2> getTexCoords();
	
		void createGridMesh();
	
		BaseSurface * clone();

	private:
		int _gridCols;
		int _gridRows;
};

} // namespace piMapper
} // namespace ofx
