// SetPresetCmd
// Sets active preset, stores previous preset index and restores it on undo.
// Created by Krisjanis Rijnieks 2016-10-07
// At the ORA bar in Berlin. Waiting for Park to celebrate his birthday.

#pragma once

#include "BaseCmd.h"
#include "BaseSurface.h"
#include "Application.h"

namespace ofx {
namespace piMapper {

class Application;

class SetPresetCmd : public BaseUndoCmd {

	public:
		SetPresetCmd(Application * app, unsigned int pi);
		void exec();
		void undo();

	private:
		Application * _app;
		unsigned int _newPresetIndex;
		unsigned int _prevPresetIndex;
		int _selectedSurfaceIndex;
};

} // namespace piMapper
} // namespace ofx

