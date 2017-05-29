#pragma once

#include "ofMain.h"
#include "BaseSurface.h"
#include "SurfaceType.h"

namespace ofx {
namespace piMapper {

// TODO: Transform this into CircleSurface.

class HexagonSurface : public BaseSurface {
	public:
		HexagonSurface();

		void setup();
		void setup(
			vector <ofDefaultVec3> & verts,
			vector <ofDefaultVec2> & coords,
			BaseSource * newSource);
		void draw();
	
		void setVertex(int index, ofDefaultVec3 v);
		void setVertices(vector<ofDefaultVec3> v);
	
		void setTexCoord(int index, ofDefaultVec2 t);
		void setTexCoords(vector<ofDefaultVec2> t);
	
		void moveBy(ofDefaultVec2 v);

		int getType();
		bool hitTest(ofDefaultVec2 p);
		ofDefaultVec3 getVertex(int index);
		ofDefaultVec2 getTexCoord(int index);
		ofPolyline getHitArea();
		ofPolyline getTextureHitArea();
		vector <ofDefaultVec3> & getVertices();
		vector <ofDefaultVec2> & getTexCoords();
	
		BaseSurface * clone();
};

} // namespace piMapper
} // namespace ofx