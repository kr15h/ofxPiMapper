#include "MvLayerUpCmd.h"

namespace ofx {
namespace piMapper {

MvLayerUpCmd::MvLayerUpCmd(SurfaceStack * stack, BaseSurface * selectedSurface){
	_stack = stack;
	_selectedSurface = selectedSurface;
	_selectedSurfaceIndex = -1;
}

void MvLayerUpCmd::exec(){
	ofLogNotice("MvLayerUpCmd", "exec");
	
	// Find selected surface index in SurfaceStack.
	for(int i = 0; i < _stack->size(); ++i){
		if(_selectedSurface == _stack->at(i)){
			_selectedSurfaceIndex = i;
			break;
		}
	}
	
	if(_selectedSurfaceIndex == -1){
		throw runtime_error("MvLayerUpCmd used with no surface selected");
	}
	
	if(_selectedSurfaceIndex == _stack->size() - 1){
		throw runtime_error("Check if selected surface is not top before using MvLayerUpCmd");
	}
	
	if(_stack->size() <= 1){
		throw runtime_error("Check if there is more than one surface before using MvLayerUpCmd");
	}
	
	// Swap it with the next surface
	_stack->swap(_selectedSurfaceIndex, _selectedSurfaceIndex + 1);
}

void MvLayerUpCmd::undo(){
	ofLogNotice("MvLayerUoCmd", "undo");
	_stack->swap(_selectedSurfaceIndex, _selectedSurfaceIndex + 1);
}

} // namespace piMapper
} // namespace ofx

