#pragma once

#include "BaseCmd.h"
#include "QuadSurface.h"
#include "SourcesEditorWidget.h"

namespace ofx {
namespace piMapper {

class SourcesEditorWidget;

class TogglePerspectiveCmd : public BaseUndoCmd {

	public:
		TogglePerspectiveCmd(QuadSurface * surface);
		void exec();
		void undo();

	private:
		QuadSurface * _surface;
		bool _perspectiveBeforeExec;

};

} // namespace piMapper
} // namespace ofx

