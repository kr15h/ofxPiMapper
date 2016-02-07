#pragma once

#include "SurfaceManager.h"
#include "BaseCmd.h"
#include "BaseSurface.h"

class ofxPiMapper;

namespace ofx {
namespace piMapper {

class DeselectSurfaceCmd : public BaseUndoCmd {

	public:
		DeselectSurfaceCmd(SurfaceManager * sm);
		void exec();
		void undo();

	private:
		SurfaceManager * _surfaceManager;
		BaseSurface * _surface;
		int _selectedVertexIndex;

};

} // namespace piMapper
} // namespace ofx

