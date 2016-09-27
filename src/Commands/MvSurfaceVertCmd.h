// MvSurfaceVertCmd
// Provides with option to undo move surface vertex operation.
// Created by Krisjanis Rijnieks 2015-05-15

#pragma once

#include "BaseCmd.h"
#include "BaseSurface.h"
#include "ProjectionEditorWidget.h"
#include "BaseJoint.h"

namespace ofx {
namespace piMapper {

class MvSurfaceVertCmd : public BaseUndoCmd {

	public:
		MvSurfaceVertCmd(int vertIndex, BaseSurface * surface);
		void exec();
		void undo();

	private:
		int _vertIndex;
		ofVec2f _prevVertPos;
		BaseSurface * _surface;

};

} // namespace piMapper
} // namespace ofx

