// TranslateCanvasCmd
// Stores and restores the canvas of a mode/state.
// Created by Krisjanis Rijnieks 2016-09-13

#pragma once

#include "BaseCmd.h"
#include "BaseSurface.h"
#include "Application.h"

namespace ofx {
namespace piMapper {

class TranslateCanvasCmd : public BaseUndoCmd {

	public:
		TranslateCanvasCmd(Application * app, ofPoint from, ofPoint to);
		void exec();
		void undo();

	private:
		Application * _app;
		ofPoint _from;
		ofPoint _to;
};

} // namespace piMapper
} // namespace ofx

