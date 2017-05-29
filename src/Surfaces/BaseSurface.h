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
		virtual ~BaseSurface();
	
		virtual void setup() = 0;
		virtual void draw() = 0;
		virtual void setVertex(int index, ofDefaultVec3 p) = 0;
		virtual void setVertices(vector<ofDefaultVec3> v) = 0;
		virtual void setTexCoord(int index, ofDefaultVec2 t) = 0;
		virtual void setTexCoords(vector<ofDefaultVec2> t) = 0;
		virtual void moveBy(ofDefaultVec2 v) = 0;
	
        virtual int getType() = 0;
	
		virtual bool hitTest(ofDefaultVec2 p) = 0;
	
		virtual ofPolyline getHitArea() = 0;
        virtual ofPolyline getTextureHitArea() = 0;
	
		virtual vector <ofDefaultVec3> & getVertices() = 0;
        virtual vector <ofDefaultVec2> & getTexCoords() = 0;
	
		virtual BaseSurface * clone() = 0;

		void drawTexture(ofDefaultVec2 position);
		void setSource(BaseSource * newSource);
		void setMoved(bool moved);
		void scaleTo(float scale);
	
		BaseSource * getSource();
		BaseSource * getDefaultSource();

		bool getMoved();
		float getScale();
	
		ofMesh & getMesh();
		ofRectangle & getBoundingBox();
	
		ofEvent <vector<ofDefaultVec3>> verticesChangedEvent;
		ofEvent <int> vertexChangedEvent;

		bool isEnabled();
		void setEnabled(bool v);


	protected:
		ofMesh mesh;
	
		ofRectangle _boundingBox;
	
		ofTexture defaultTexture;
	
		BaseSource * source;
		BaseSource * defaultSource;
	
		void createDefaultTexture();
	
		bool _moved;

		bool _enabled = true;
	
		float _scale;
};

} // namespace piMapper
} // namespace ofx
