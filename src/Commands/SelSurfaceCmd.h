// SelSurfaceCmd
// Provides with option to undo select surface operation.
// Created by Krisjanis Rijnieks 2015-05-14

#pragma once

#include "BaseCmd.h"
#include "BaseSurface.h"
#include "SurfaceManager.h"
#include "ProjectionEditor.h"

namespace ofx {
namespace piMapper {

class SelSurfaceCmd : public BaseUndoCmd {

	public:
		SelSurfaceCmd(SurfaceManager * surfaceManager,
					  BaseSurface * surfaceToSelect,
					  ProjectionEditor * projectionEditor);
		void exec();
		void undo();

	private:
		BaseSurface * _surfaceToSelect;
		SurfaceManager * _surfaceManager;
		BaseSurface * _prevSelectedSurface;
		ProjectionEditor * _projectionEditor;

};

} // namespace piMapper
} // namespace ofx

