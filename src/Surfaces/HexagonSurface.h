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
			std::vector<Vec3> & verts,
			std::vector<Vec2> & coords,
			BaseSource * newSource);
		void draw();
		void setVertex(int index, Vec3 p);
		void setVertices(std::vector<Vec3> v);
		void setTexCoord(int index, Vec2 t);
		void setTexCoords(std::vector<Vec2> t);
		void moveBy(Vec3 v);
        void fullScreen();

		int getType();
		bool hitTest(Vec2 p);
		Vec3 getVertex(int index);
		Vec2 getTexCoord(int index);
		ofPolyline getHitArea();
		ofPolyline getTextureHitArea();
		std::vector<Vec3> getVertices();
		std::vector<Vec2> getTexCoords();
	
		BaseSurface * clone();
};

} // namespace piMapper
} // namespace ofx
