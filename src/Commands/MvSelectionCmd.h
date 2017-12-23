#pragma once

#include "BaseCmd.h"
#include "SurfaceManager.h"
#include "Vec2.h"

namespace ofx {
namespace piMapper {

class MvSelectionCmd : public BaseUndoCmd {

	public:
		MvSelectionCmd(SurfaceManager * sm, Vec2 moveBy);
		void exec();
		void undo();

	private:
		SurfaceManager * _surfaceManager;
		Vec2 _movedBy;

};

} // namespace piMapper
} // namespace ofx

