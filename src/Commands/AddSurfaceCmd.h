#pragma once

#include "SurfaceManager.h"
#include "BaseCmd.h"
#include "SurfaceType.h"
#include "BaseSurface.h"
#include "SurfaceFactory.h"

class ofxPiMapper;

namespace ofx {
namespace piMapper {

class AddSurfaceCmd : public BaseUndoCmd {

	public:
		AddSurfaceCmd(SurfaceManager * sm, SurfaceType surfaceType);
		void exec();
		void undo();

	private:
		SurfaceManager * _surfaceManager;
		SurfaceType _surfaceType;
		BaseSurface * _selectedSurface;

};

} // namespace piMapper
} // namespace ofx

