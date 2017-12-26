#pragma once

#include "ofMain.h"
#include "BaseSurface.h"
#include "SurfaceType.h"
#include "Vec2.h"
#include "Vec3.h"

namespace ofx {
namespace piMapper {

// TODO: Transform this into CircleSurface.

class HexagonSurface : public BaseSurface {
	public:
		HexagonSurface();

		void setup();
		void setup(
			vector <Vec3> & verts,
			vector <Vec2> & coords,
			BaseSource * newSource);
		void draw();
		void setVertex(int index, Vec3 p);
		void setVertices(vector<Vec3> v);
		void setTexCoord(int index, Vec2 t);
		void setTexCoords(vector<Vec2> t);
		void moveBy(Vec3 v);

		int getType();
		bool hitTest(Vec2 p);
		Vec3 getVertex(int index);
		Vec2 getTexCoord(int index);
		ofPolyline getHitArea();
		ofPolyline getTextureHitArea();
		vector<Vec3> getVertices();
		vector<Vec2> getTexCoords();
	
		BaseSurface * clone();
};

} // namespace piMapper
} // namespace ofx
