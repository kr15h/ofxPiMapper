#pragma once

#include "ofMain.h"
#include <string>
#include "BaseSource.h"

using namespace std;

namespace ofx {
namespace piMapper {

class BaseSurface {

	public:
		BaseSurface();
		~BaseSurface();
		virtual void setup(){}
		virtual void draw(){}
	
		virtual void setVertex(int index, ofVec2f p){}
		virtual void setVertices(vector<ofVec2f> v){}
	
		virtual void setTexCoord(int index, ofVec2f t){}
		virtual void setTexCoords(vector<ofVec2f> t){}
	
		virtual void moveBy(ofVec2f v){}
		virtual int getType(){}
		virtual bool hitTest(ofVec2f p){}
		virtual ofPolyline getHitArea(){}
		virtual ofPolyline getTextureHitArea(){}
		virtual vector <ofVec3f> & getVertices(){}
		virtual vector <ofVec2f> & getTexCoords(){}
	
		virtual BaseSurface * clone(){}

		void drawTexture(ofVec2f position);
		void setSource(BaseSource * newSource);
		BaseSource * getSource();
		BaseSource * getDefaultSource();

		void setMoved(bool moved);
		bool getMoved();
	
		ofMesh & getMesh();
	
		// TODO: The surface should emit an event once vertex has changed
		ofEvent <vector<ofVec3f>> verticesChangedEvent;
		ofEvent <int> vertexChangedEvent;

	protected:
		ofMesh mesh;
		ofTexture defaultTexture;
		BaseSource * source;
		BaseSource * defaultSource;
		void createDefaultTexture();
		bool _moved;

};

} // namespace piMapper
} // namespace ofx