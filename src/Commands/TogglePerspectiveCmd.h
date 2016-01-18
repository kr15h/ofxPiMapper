#pragma once

#include "BaseCmd.h"
#include "QuadSurface.h"
#include "SourcesEditor.h"

namespace ofx {
namespace piMapper {

class SourcesEditor;

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

