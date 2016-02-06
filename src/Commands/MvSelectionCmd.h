#pragma once

#include "BaseCmd.h"
#include "SurfaceManager.h"

namespace ofx {
namespace piMapper {

class MvSelectionCmd : public BaseUndoCmd {

	public:
		MvSelectionCmd(SurfaceManager * sm, ofVec2f moveBy);
		void exec();
		void undo();

	private:
		SurfaceManager * _surfaceManager;
		ofVec2f _movedBy;

};

} // namespace piMapper
} // namespace ofx

