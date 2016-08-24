#pragma once

#include "BaseCmd.h"
#include "BaseSurface.h"

namespace ofx {
namespace piMapper {

class ScaleSurfaceFromToCmd : public BaseUndoCmd {

	public:
		ScaleSurfaceFromToCmd(BaseSurface * selectedSurface, float from, float to);
		void exec();
		void undo();

	private:
		BaseSurface * _selectedSurface;
	
		float _scaleFrom;
		float _scaleTo;

};

} // namespace piMapper
} // namespace ofx

