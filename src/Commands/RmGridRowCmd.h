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

class RmGridRowCmd : public BaseUndoCmd {

	public:
		RmGridRowCmd(GridWarpSurface * s);
		void exec();
		void undo();

	private:
		vector <Vec3> _vertices;
		vector <Vec2> _texCoords;
		GridWarpSurface * _surface;
		bool _doNotUndo;

};

} // namespace piMapper
} // namespace ofx

