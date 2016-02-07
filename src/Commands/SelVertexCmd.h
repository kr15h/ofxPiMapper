#pragma once

#include "BaseCmd.h"
#include "SurfaceManager.h"

class ofxPiMapper;

namespace ofx {
namespace piMapper {

class SelVertexCmd : public BaseUndoCmd {

	public:
		SelVertexCmd(SurfaceManager * sm, int i);
		void exec();
		void undo();

	private:
		SurfaceManager * _surfaceManager;
		int _newVertexIndex;
		int _prevVertexIndex;

};

} // namespace piMapper
} // namespace ofx

