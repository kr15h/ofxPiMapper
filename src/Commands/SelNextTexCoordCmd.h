#pragma once

#include "BaseCmd.h"
#include "TextureEditor.h"

class ofxPiMapper;

namespace ofx {
namespace piMapper {

class SelNextTexCoordCmd : public BaseUndoCmd {

	public:
		SelNextTexCoordCmd(TextureEditor * te);
		void exec();
		void undo();

	private:
		TextureEditor * _textureEditor;

};

} // namespace piMapper
} // namespace ofx

