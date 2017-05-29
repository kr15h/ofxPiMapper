#pragma once

#include "SurfaceManager.h"
#include "BaseCmd.h"
#include "GridWarpSurface.h"
#include "ProjectionEditorWidget.h"

class ofxPiMapper;

namespace ofx {
namespace piMapper {

class RmGridColCmd : public BaseUndoCmd {

	public:
		RmGridColCmd(GridWarpSurface * s);
		void exec();
		void undo();

	private:
		vector <ofDefaultVec3> _vertices;
		vector <ofDefaultVec2> _texCoords;
		GridWarpSurface * _surface;
		bool _doNotUndo;

};

} // namespace piMapper
} // namespace ofx

