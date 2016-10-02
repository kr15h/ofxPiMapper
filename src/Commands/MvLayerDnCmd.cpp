#include "MvLayerDnCmd.h"

namespace ofx {
namespace piMapper {

MvLayerDnCmd::MvLayerDnCmd(SurfaceStack * stack, BaseSurface * selectedSurface){
	_stack = stack;
	_selectedSurface = selectedSurface;
	_selectedSurfaceIndex = -1;
}

void MvLayerDnCmd::exec(){
	ofLogNotice("MvLayerDnCmd", "exec");
	
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
	
	if(_selectedSurfaceIndex == 0){
		throw runtime_error("Check if selected surface is not bottom before using MvLayerUpCmd");
	}
	
	if(_stack->size() <= 1){
		throw runtime_error("Check if there is more than one surface before using MvLayerUpCmd");
	}
	
	// Swap it with the previous surface
	_stack->swap(_selectedSurfaceIndex, _selectedSurfaceIndex - 1);
}

void MvLayerDnCmd::undo(){
	ofLogNotice("MvLayerDnCmd", "undo");
	_stack->swap(_selectedSurfaceIndex, _selectedSurfaceIndex - 1);
}

} // namespace piMapper
} // namespace ofx

