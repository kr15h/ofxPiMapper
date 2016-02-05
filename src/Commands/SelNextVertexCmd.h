#pragma once

#include "BaseCmd.h"
#include "SurfaceManager.h"

class ofxPiMapper;

namespace ofx {
namespace piMapper {

class SelNextVertexCmd : public BaseUndoCmd {

	public:
		SelNextVertexCmd(SurfaceManager * sm);
		void exec();
		void undo();

	private:
		SurfaceManager * _surfaceManager;

};

} // namespace piMapper
} // namespace ofx

