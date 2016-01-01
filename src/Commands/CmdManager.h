#pragma once

#include <vector>
#include "BaseCmd.h"
#include "ofLog.h"

namespace ofx {
namespace piMapper {

class CmdManager {

	public:
		void exec(BaseCmd * cmd);
		void undo();

	private:
		vector <BaseUndoCmd *> cmdStack;

};

} // namespace piMapper
} // namespace ofx