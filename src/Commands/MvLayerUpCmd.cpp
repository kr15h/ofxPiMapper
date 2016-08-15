#include "MvLayerUpCmd.h"

namespace ofx {
namespace piMapper {

MvLayerUpCmd::MvLayerUpCmd(BaseSurface * selectedSurface){
	_selectedSurface = selectedSurface;
	_selectedSurfaceIndex = -1;
}

void MvLayerUpCmd::exec(){
	ofLogNotice("MvLayerUpCmd", "exec");
	
	// Find selected surface index in SurfaceStack.
	for(int i = 0; i < SurfaceStack::instance()->size(); ++i){
		if(_selectedSurface == SurfaceStack::instance()->at(i)){
			_selectedSurfaceIndex = i;
			break;
		}
	}
	
	if(_selectedSurfaceIndex == -1){
		throw runtime_error("MvLayerUpCmd used with no surface selected");
	}
	
	if(_selectedSurfaceIndex == SurfaceStack::instance()->size() - 1){
		throw runtime_error("Check if selected surface is not top before using MvLayerUpCmd");
	}
	
	if(SurfaceStack::instance()->size() <= 1){
		throw runtime_error("Check if there is more than one surface before using MvLayerUpCmd");
	}
	
	// Swap it with the next surface
	SurfaceStack::instance()->swap(_selectedSurfaceIndex, _selectedSurfaceIndex + 1);
}

void MvLayerUpCmd::undo(){
	ofLogNotice("MvLayerUoCmd", "undo");
	SurfaceStack::instance()->swap(_selectedSurfaceIndex, _selectedSurfaceIndex + 1);
}

} // namespace piMapper
} // namespace ofx

