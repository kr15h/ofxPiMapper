#pragma once

#include "BaseCmd.h"
#include "BaseSurface.h"

namespace ofx {
namespace piMapper {

class StartDragSurfaceCmd : public BaseUndoCmd {

	public:
		StartDragSurfaceCmd(BaseSurface * surface);
		void exec();
		void undo();

	private:
		BaseSurface * _surface;
		vector <ofDefaultVec3> _previousVertices;

};

} // namespace piMapper
} // namespace ofx

