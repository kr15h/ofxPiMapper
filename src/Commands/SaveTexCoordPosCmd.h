// SaveTexCoordPosCmd
// Saves current position of the texture coordinate and resets it.
// Created by Krisjanis Rijnieks 2016-10-30

#pragma once

#include "BaseCmd.h"
#include "CircleJoint.h"
#include "Gui.h"

namespace ofx {
namespace piMapper {

class SaveTexCoordPosCmd : public BaseUndoCmd {

	public:
		SaveTexCoordPosCmd(int texCoordIndex, ofVec2f position);
		void exec();
		void undo();

	private:
		int _texCoordIndex;
		ofVec2f _position;

};

} // namespace piMapper
} // namespace ofx

