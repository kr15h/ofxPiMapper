// MvTexCoordCmd
// Move texture coordinate of a selected surface and be able to undo it
// Created by Krisjanis Rijnieks 2015-05-19

#pragma once

#include "BaseCmd.h"
#include "CircleJoint.h"
#include "Gui.h"
#include "Vec2.h"

namespace ofx {
namespace piMapper {

class MvTexCoordCmd : public BaseUndoCmd {

	public:
		MvTexCoordCmd(int texCoordIndex, Vec2 by);
		void exec();
		void undo();

	private:
		int _texCoordIndex;
		Vec2 _moveBy;
		Vec2 _positionBefore;

};

} // namespace piMapper
} // namespace ofx

