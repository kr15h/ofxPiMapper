#pragma once

#include "ofEvents.h"

#include "BaseSurface.h"
#include "GridWarpSurface.h"
#include "CircleJoint.h"
#include "SurfaceType.h"

namespace ofx {
namespace piMapper {

class TextureEditor {

	public:
		TextureEditor();
		~TextureEditor();

		void registerAppEvents();
		void unregisterAppEvents();
		void registerKeyEvents();
		void unregisterKeyEvents();
		void enable();
		void disable();

		void update(); // Maybe the Application pointer would make sense there. Not sure yet.
		void keyPressed(ofKeyEventArgs & args);
		void keyReleased(ofKeyEventArgs & args);
		void mousePressed(ofMouseEventArgs & args);
		void mouseDragged(ofMouseEventArgs & args);
		void draw();
		void drawJoints();
		void setSurface(BaseSurface * newSurface);
		void clear();
		void createJoints();
		void clearJoints();
		void unselectAllJoints();
		void selectNextTexCoord();
		void selectPrevTexCoord();
		void moveTexCoords(ofVec2f by);
		void stopDragJoints();
		void moveSelection(ofVec2f by);
		void constrainJointsToQuad(int selectedJointIndex);
		CircleJoint * hitTestJoints(ofVec2f pos);
		vector <CircleJoint *> & getJoints();

	private:
		BaseSurface * surface;
		vector <CircleJoint *> joints;
		bool bShiftKeyDown;

};

} // namespace piMapper
} // namespace ofx