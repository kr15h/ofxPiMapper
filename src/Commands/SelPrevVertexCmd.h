#pragma once

#include "BaseCmd.h"
#include "SurfaceManager.h"

class ofxPiMapper;

namespace ofx {
namespace piMapper {

class SelPrevVertexCmd : public BaseUndoCmd {

	public:
		SelPrevVertexCmd(SurfaceManager * sm);
		void exec();
		void undo();

	private:
		SurfaceManager * _surfaceManager;

};

} // namespace piMapper
} // namespace ofx

