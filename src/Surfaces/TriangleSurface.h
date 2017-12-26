#pragma once

#include "ofMain.h"
#include "BaseSurface.h"
#include "SurfaceType.h"
#include "Vec2.h"
#include "Vec3.h"

namespace ofx {
namespace piMapper {

class TriangleSurface : public BaseSurface {
	public:
		TriangleSurface();

		void setup();
		void setup(
			Vec3 p1, Vec3 p2, Vec3 p3,
			Vec2 t1, Vec2 t2, Vec2 t3,
			BaseSource * newSource);
		void draw();
		void setVertex(int index, Vec3 p);
		void setVertices(std::vector<Vec3> v);
		void setTexCoord(int index, Vec2 t);
		void setTexCoords(std::vector<Vec2> t);
		void moveBy(Vec3 v);

		int getType();
		bool hitTest(Vec2 p);
		Vec2 getVertex(int index);
		Vec2 getTexCoord(int index);
		ofPolyline getHitArea();
		ofPolyline getTextureHitArea();
		std::vector<Vec3> getVertices();
		std::vector<Vec2> getTexCoords();
	
		BaseSurface * clone();
};

} // namespace piMapper
} // namespace ofx
