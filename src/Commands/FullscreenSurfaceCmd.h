// FullscreenSurfaceCmd
// Makes selected surface resize to fit the screen
// Created by Pierre Proske 25-03-2020

#pragma once

#include "BaseCmd.h"
#include "BaseSurface.h"
#include "SurfaceManager.h"
#include "Vec3.h"

namespace ofx {
namespace piMapper {

class FullscreenSurfaceCmd : public BaseUndoCmd {

	public:
        FullscreenSurfaceCmd(BaseSurface * surface);
		void exec();
		void undo();

	private:
		BaseSurface * _surface;
        std::vector<Vec3> _previousVertices;
};

} // namespace piMapper
} // namespace ofx

