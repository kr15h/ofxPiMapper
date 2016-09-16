// SetTexMapDrawMode
// Sets draw mode of the texture mapping state
// Created by Krisjanis Rijnieks 2016-09-16

#pragma once

#include "BaseCmd.h"
#include "TextureMappingState.h"

namespace ofx {
namespace piMapper {

class SetTexMapDrawModeCmd : public BaseUndoCmd {

	public:
		SetTexMapDrawModeCmd(TextureMappingState * s, int m);
		void exec();
		void undo();

	private:
		TextureMappingState * _state;
		int _oldMode;
		int _newMode;

};

} // namespace piMapper
} // namespace ofx

