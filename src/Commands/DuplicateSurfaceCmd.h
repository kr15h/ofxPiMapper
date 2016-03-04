// DuplicateSurfaceCmd
// Duplicates selected surface
// Created by Krisjanis Rijnieks 2016-03-04

#pragma once

#include "BaseCmd.h"
#include "BaseSurface.h"
#include "SurfaceManager.h"

namespace ofx {
namespace piMapper {

class DuplicateSurfaceCmd : public BaseUndoCmd {

	public:
		DuplicateSurfaceCmd(BaseSurface * surface, SurfaceManager * surfaceManager);
		void exec();
		void undo();

	private:
		BaseSurface * _surface;
		BaseSurface * _duplicate;
		SurfaceManager * _surfaceManager;

};

} // namespace piMapper
} // namespace ofx

