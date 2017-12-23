#pragma once

#include "ofMain.h"
#include "BaseSurface.h"
#include "SurfaceType.h"
#include "HomographyHelper.h"
#include "Vec2.h"

namespace ofx {
namespace piMapper {

class QuadSurface : public BaseSurface {
	public:
		QuadSurface();
		~QuadSurface();

		void setup();
		void setup(Vec2 p1, Vec2 p2, Vec2 p3, Vec2 p4, Vec2 t1,
				   Vec2 t2, Vec2 t3, Vec2 t4, BaseSource * newSource);

		void draw();
	
		void setVertex(int index, Vec2 p);
		void setVertices(vector<Vec2> v);
		void setVertices(vector<ofVec3f> v);
	
		void setTexCoord(int index, Vec2 t);
		void setTexCoords(vector<Vec2> t);
	
		void moveBy(Vec2 v);

		int getType();
		bool hitTest(Vec2 p);
		Vec2 getVertex(int index);
		Vec2 getTexCoord(int index);
		ofPolyline getHitArea();
		ofPolyline getTextureHitArea();
		vector <ofVec3f> & getVertices();
		vector <Vec2> & getTexCoords();
	
		void setPerspectiveWarping(bool b);
		bool getPerspectiveWarping();
	
		ofRectangle getMeshBoundingBox();
	
		BaseSurface * clone();

	private:
		void calculateHomography();
	
		float _matrix[16];
		bool _perspectiveWarping;
};

} // namespace piMapper
} // namespace ofx
