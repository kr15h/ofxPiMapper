// SelSurfaceCmd
// Provides with option to undo select surface operation.
// Created by Krisjanis Rijnieks 2015-05-14

#pragma once

#include "BaseCmd.h"
#include "BaseSurface.h"
#include "SurfaceManager.h"
#include "Gui.h"

namespace ofx {
namespace piMapper {

class SelSurfaceCmd : public BaseUndoCmd {

	public:
		SelSurfaceCmd(SurfaceManager * surfaceManager, BaseSurface * surfaceToSelect);
		void exec();
		void undo();

	private:
		BaseSurface * _surfaceToSelect;
		SurfaceManager * _surfaceManager;
		BaseSurface * _prevSelectedSurface;
		int _prevSelectedVertex;

};

} // namespace piMapper
} // namespace ofx

