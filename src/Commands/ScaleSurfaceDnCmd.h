#pragma once

#include "BaseCmd.h"
#include "BaseSurface.h"

namespace ofx {
namespace piMapper {

class ScaleSurfaceDnCmd : public BaseUndoCmd {

	public:
		ScaleSurfaceDnCmd(BaseSurface * selectedSurface, float by);
		void exec();
		void undo();

	private:
		BaseSurface * _selectedSurface;
	
		float _by;

};

} // namespace piMapper
} // namespace ofx

