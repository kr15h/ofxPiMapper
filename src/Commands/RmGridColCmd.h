#pragma once

#include "SurfaceManager.h"
#include "BaseCmd.h"
#include "GridWarpSurface.h"
#include "ProjectionEditor.h"

class ofxPiMapper;

namespace ofx {
namespace piMapper {

class RmGridColCmd : public BaseUndoCmd {

	public:
		RmGridColCmd(GridWarpSurface * s, ProjectionEditor * e);
		void exec();
		void undo();

	private:
		vector <ofVec3f> _vertices;
		vector <ofVec2f> _texCoords;
		GridWarpSurface * _surface;
		ProjectionEditor * _editor;
		bool _doNotUndo;

};

} // namespace piMapper
} // namespace ofx

