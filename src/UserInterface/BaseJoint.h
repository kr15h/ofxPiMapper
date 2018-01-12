#pragma once

#include "ofMain.h"
#include "Vec2.h"

namespace ofx {
namespace piMapper {

class BaseJoint {

	public:
		BaseJoint();

		Vec2 position;
		bool enabled;
		bool visible;
		bool selected;

		void mousePressed(ofMouseEventArgs & args);
		void mouseReleased(int x, int y, int button);
		void mouseDragged(ofMouseEventArgs & args);
		void startDrag();
		void stopDrag();
		void select();
		void unselect();
		void setClickDistance(Vec2 newClickDistance);
		bool isDragged();
		bool isSelected();

		virtual void update(){}
		virtual void draw(){}
		virtual bool hitTest(Vec2 position){ return false; }

	protected:
		ofColor fillColor;
		ofColor strokeColor;
		ofColor fillColorSelected;
		ofColor strokeColorSelected;
		float strokeWidth;
		Vec2 clickDistance; // How far from the center of the joint the user has
		                       // clicked?
		bool bDrag;

	private:
		void setDefaultColors();
		void setDefaultProperties();

};

} // namespace piMapper
} // namespace ofx
