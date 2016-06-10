// ToggleAnimatedSourceCmd
// Toggles playing of animated (video, gif) sources
// Created by Krisjanis Rijnieks 2016-06-10

#pragma once

#include "BaseCmd.h"
#include "BaseSurface.h"
#include "SourceType.h"
#include "VideoSource.h"

namespace ofx {
namespace piMapper {

class ToggleAnimatedSourceCmd : public BaseUndoCmd {

	public:
		ToggleAnimatedSourceCmd(BaseSurface * surface);
		void exec();
		void undo();

	private:
        BaseSurface * _surface;
    
};

} // namespace piMapper
} // namespace ofx

