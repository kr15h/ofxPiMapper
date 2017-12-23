#pragma once

#include "ofEvents.h"

#include "BaseSurface.h"
#include "GridWarpSurface.h"
#include "CircleJoint.h"
#include "SurfaceType.h"
#include "GuiBaseWidget.h"
#include "Vec2.h"

namespace ofx {
namespace piMapper {

class TextureEditorWidget : public GuiBaseWidget {

	public:
		TextureEditorWidget();

		void setup();
		void update(); // Maybe the Application pointer would make sense there. Not sure yet.
		void draw();
	
		void onMousePressed(ofMouseEventArgs & e);
		void onMouseReleased(ofMouseEventArgs & e);
		void onMouseDragged(ofMouseEventArgs & e);
	
		bool inside(float x, float y){ return false; }
	
		void drawJoints();
		void setSurface(BaseSurface * newSurface);
		void clear();
		void createJoints();
		void clearJoints();
		void unselectAllJoints();
	
		void selectTexCoord(int i);
		int getSelectedTexCoord();
		void selectNextTexCoord();
		void selectPrevTexCoord();
	
		void moveTexCoords(Vec2 by);
		void moveTexCoordTo(int texCoordIndex, Vec2 position);
	
		void stopDragJoints();
		void moveSelection(Vec2 by);
		void constrainJointsToQuad(int selectedJointIndex);
		CircleJoint * hitTestJoints(Vec2 pos);
		vector <CircleJoint *> & getJoints();

	private:
		BaseSurface * surface;
		vector <CircleJoint *> joints;
	
		bool bShiftKeyDown;
		bool _pollCreateJoints;

};

} // namespace piMapper
} // namespace ofx
