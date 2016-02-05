#pragma once

#include "BaseCmd.h"
#include "BaseSurface.h"

class ofxPiMapper;

namespace ofx {
namespace piMapper {

class SelNextVertexCmd : public BaseUndoCmd {

	public:
		SelNextVertexCmd(BaseSurface * s);
		void exec();
		void undo();

	private:
		BaseSurface * _surface;
		int _prevVertexIndex;

};

} // namespace piMapper
} // namespace ofx

