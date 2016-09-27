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
		vector <ofVec3f> _vertices;
		vector <ofVec2f> _texCoords;
		GridWarpSurface * _surface;
		bool _doNotUndo;

};

} // namespace piMapper
} // namespace ofx

