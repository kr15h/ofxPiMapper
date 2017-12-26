#pragma once

#include "BaseCmd.h"
#include "BaseSurface.h"
#include "Vec3.h"

namespace ofx {
namespace piMapper {

class StartDragSurfaceCmd : public BaseUndoCmd {

	public:
		StartDragSurfaceCmd(BaseSurface * surface);
		void exec();
		void undo();

	private:
		BaseSurface * _surface;
		vector <Vec3> _previousVertices;

};

} // namespace piMapper
} // namespace ofx

