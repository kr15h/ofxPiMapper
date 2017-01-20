// RmSurfaceCmd
// Provides with option to undo remove surface operation.
// Created by Krisjanis Rijnieks 2015-05-14

#pragma once

#include "SurfaceManager.h"
#include "BaseCmd.h"
#include "BaseSurface.h"

class ofxPiMapper;

namespace ofx {
namespace piMapper {

class RmSurfaceCmd : public BaseUndoCmd {

	public:
		RmSurfaceCmd(SurfaceManager * sm, int i);
		void exec();
		void undo();

	private:
		SurfaceManager * _surfaceManager;
		BaseSurface * _surface;
		int _surfaceIndex;

};

} // namespace piMapper
} // namespace ofx

