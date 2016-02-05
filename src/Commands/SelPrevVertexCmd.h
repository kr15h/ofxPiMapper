#pragma once

#include "BaseCmd.h"
#include "BaseSurface.h"

class ofxPiMapper;

namespace ofx {
namespace piMapper {

class SelPrevVertexCmd : public BaseUndoCmd {

	public:
		SelPrevVertexCmd(BaseSurface * s);
		void exec();
		void undo();

	private:
		BaseSurface * _surface;

};

} // namespace piMapper
} // namespace ofx

