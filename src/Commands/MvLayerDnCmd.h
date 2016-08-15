#pragma once

#include "BaseCmd.h"
#include "BaseSurface.h"
#include "SurfaceStack.h"

namespace ofx {
namespace piMapper {

class MvLayerDnCmd : public BaseUndoCmd {

	public:
		MvLayerDnCmd(BaseSurface * selectedSurface);
		void exec();
		void undo();

	private:
		BaseSurface * _selectedSurface;
	
		int _selectedSurfaceIndex;

};

} // namespace piMapper
} // namespace ofx

