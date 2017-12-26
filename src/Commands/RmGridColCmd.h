#pragma once

#include "SurfaceManager.h"
#include "BaseCmd.h"
#include "GridWarpSurface.h"
#include "ProjectionEditorWidget.h"
#include "Vec2.h"
#include "Vec3.h"

class ofxPiMapper;

namespace ofx {
namespace piMapper {

class RmGridColCmd : public BaseUndoCmd {

	public:
		RmGridColCmd(GridWarpSurface * s);
		void exec();
		void undo();

	private:
		std::vector<Vec3> _vertices;
		std::vector<Vec2> _texCoords;
		GridWarpSurface * _surface;
		bool _doNotUndo;

};

} // namespace piMapper
} // namespace ofx

