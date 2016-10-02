#pragma once

#include "BaseCmd.h"
#include "BaseSurface.h"
#include "SurfaceStack.h"

namespace ofx {
namespace piMapper {

class MvLayerDnCmd : public BaseUndoCmd {

	public:
		MvLayerDnCmd(SurfaceStack * stack, BaseSurface * selectedSurface);
		void exec();
		void undo();

	private:
		SurfaceStack * _stack;
	
		BaseSurface * _selectedSurface;
	
		int _selectedSurfaceIndex;

};

} // namespace piMapper
} // namespace ofx

