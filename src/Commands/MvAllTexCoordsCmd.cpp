#include "MvAllTexCoordsCmd.h"

namespace ofx {
namespace piMapper {

MvAllTexCoordsCmd::MvAllTexCoordsCmd(BaseSurface * surface, TextureEditorWidget * texEditor){
	_surface = surface;
	_texEditor = texEditor;
}

void MvAllTexCoordsCmd::exec(){
	ofLogNotice("MvAllTexCoordsCmd", "exec");
	_texCoords = _surface->getTexCoords();
}

void MvAllTexCoordsCmd::undo(){
	ofLogNotice("MvAllTexCoordsCmd", "undo");
	ofVec2f dist = _texCoords[0] - _surface->getTexCoords()[0];
	dist.x = _surface->getSource()->getTexture()->getWidth() * dist.x;
	dist.y = _surface->getSource()->getTexture()->getHeight() * dist.y;
	_texEditor->moveTexCoords(dist);
	_surface = 0;
}

} // namespace piMapper
} // namespace ofx

