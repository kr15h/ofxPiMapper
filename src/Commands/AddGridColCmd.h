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

class AddGridColCmd : public BaseUndoCmd {

	public:
		AddGridColCmd(GridWarpSurface * s);
		void exec();
		void undo();

	private:
		vector<Vec3> _vertices;
		vector<Vec2> _texCoords;
		GridWarpSurface * _surface;

};

} // namespace piMapper
} // namespace ofx

