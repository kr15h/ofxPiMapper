#pragma once

#include "SurfaceManager.h"
#include "CircleJoint.h"

namespace ofx {
namespace piMapper {

class ProjectionEditorWidget {
	
    public:
		ProjectionEditorWidget();
	
		void update();
		void draw();
	
		void mouseDragged(ofMouseEventArgs & args);
		void gotMessage(ofMessage & msg);
	
		void setSurfaceManager(SurfaceManager * newSurfaceManager);
		void clearJoints();
		void createJoints();
		void updateJoints();
		void unselectAllJoints();
		void moveSelectedSurface(ofVec2f by);
		void stopDragJoints();
		void updateVertices();
		void setSnapDistance(float newSnapDistance);
		CircleJoint * hitTestJoints(ofVec2f pos);
		vector <CircleJoint *> * getJoints();
	
		void onVertexChanged(int & i);
		void onVerticesChanged(vector<ofVec3f> & vertices);
		void onSurfaceSelected(int & surfaceIndex);
		void onVertexSelected(int & vertexIndex);
		void onVertexUnselected(int & vertexIndex);

	private:
		SurfaceManager * surfaceManager;
		vector <CircleJoint *> joints;
		bool bShiftKeyDown;
		float fSnapDistance;

		void drawJoints();

};

} // namespace piMapper
} // namespace ofx