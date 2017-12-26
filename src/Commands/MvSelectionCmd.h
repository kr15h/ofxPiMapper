#pragma once

#include "BaseCmd.h"
#include "SurfaceManager.h"
#include "Vec3.h"

namespace ofx {
namespace piMapper {

class MvSelectionCmd : public BaseUndoCmd {

	public:
		MvSelectionCmd(SurfaceManager * sm, Vec3 moveBy);
		void exec();
		void undo();

	private:
		SurfaceManager * _surfaceManager;
		Vec3 _movedBy;

};

} // namespace piMapper
} // namespace ofx

