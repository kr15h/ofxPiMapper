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
	
		virtual void setup() = 0;
		virtual void draw() = 0;
		virtual void setVertex(int index, ofVec2f p) = 0;
		virtual void setVertices(vector<ofVec2f> v) = 0;
		virtual void setTexCoord(int index, ofVec2f t) = 0;
		virtual void setTexCoords(vector<ofVec2f> t) = 0;
		virtual void moveBy(ofVec2f v) = 0;
	
        virtual int getType() = 0;
	
		virtual bool hitTest(ofVec2f p) = 0;
	
		virtual ofPolyline getHitArea() = 0;
        virtual ofPolyline getTextureHitArea() = 0;
	
		virtual vector <ofVec3f> & getVertices() = 0;
        virtual vector <ofVec2f> & getTexCoords() = 0;
	
		virtual BaseSurface * clone() = 0;

		void drawTexture(ofVec2f position);
		void setSource(BaseSource * newSource);
		void setMoved(bool moved);
		void scaleTo(float scale);
	
		BaseSource * getSource();
		BaseSource * getDefaultSource();

		bool getMoved();
		float getScale();
	
		ofMesh & getMesh();
		ofRectangle & getBoundingBox();
	
		ofEvent <vector<ofVec3f>> verticesChangedEvent;
		ofEvent <int> vertexChangedEvent;

	protected:
		ofMesh mesh;
	
		ofRectangle _boundingBox;
	
		ofTexture defaultTexture;
	
		BaseSource * source;
		BaseSource * defaultSource;
	
		void createDefaultTexture();
	
		bool _moved;
	
		float _scale;
};

} // namespace piMapper
} // namespace ofx