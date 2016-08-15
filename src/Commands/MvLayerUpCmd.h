#pragma once

#include "BaseCmd.h"
#include "BaseSurface.h"
#include "SurfaceStack.h"

namespace ofx {
namespace piMapper {

class MvLayerUpCmd : public BaseUndoCmd {

	public:
		MvLayerUpCmd(BaseSurface * selectedSurface);
		void exec();
		void undo();

	private:
		BaseSurface * _selectedSurface;
	
		int _selectedSurfaceIndex;

};

} // namespace piMapper
} // namespace ofx

