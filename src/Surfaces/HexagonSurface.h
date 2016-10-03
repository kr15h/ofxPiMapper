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
			vector <ofVec2f> & verts,
			vector <ofVec2f> & coords,
			BaseSource * newSource);
		void draw();
	
		void setVertex(int index, ofVec2f p);
		void setVertices(vector<ofVec2f> v);
		void setVertices(vector<ofVec3f> v);
	
		void setTexCoord(int index, ofVec2f t);
		void setTexCoords(vector<ofVec2f> t);
	
		void moveBy(ofVec2f v);

		int getType();
		bool hitTest(ofVec2f p);
		ofVec2f getVertex(int index);
		ofVec2f getTexCoord(int index);
		ofPolyline getHitArea();
		ofPolyline getTextureHitArea();
		vector <ofVec3f> & getVertices();
		vector <ofVec2f> & getTexCoords();
	
		BaseSurface * clone();
};

} // namespace piMapper
} // namespace ofx