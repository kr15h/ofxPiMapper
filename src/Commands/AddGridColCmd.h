#pragma once

#include "SurfaceManager.h"
#include "BaseCmd.h"
#include "GridWarpSurface.h"
#include "ProjectionEditorWidget.h"

class ofxPiMapper;

namespace ofx {
namespace piMapper {

class AddGridColCmd : public BaseUndoCmd {

	public:
		AddGridColCmd(GridWarpSurface * s);
		void exec();
		void undo();

	private:
		vector <ofDefaultVec3> _vertices;
		vector <ofDefaultVec2> _texCoords;
		GridWarpSurface * _surface;

};

} // namespace piMapper
} // namespace ofx

