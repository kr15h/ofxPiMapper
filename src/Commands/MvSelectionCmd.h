#pragma once

#include "BaseCmd.h"
#include "SurfaceManager.h"

namespace ofx {
namespace piMapper {

class MvSelectionCmd : public BaseUndoCmd {

	public:
		MvSelectionCmd(SurfaceManager * sm, ofDefaultVec2 moveBy);
		void exec();
		void undo();

	private:
		SurfaceManager * _surfaceManager;
		ofDefaultVec2 _movedBy;

};

} // namespace piMapper
} // namespace ofx

