#include "CmdManager.h"

namespace ofx {
namespace piMapper {

void CmdManager::exec(BaseCmd * cmd){
	cmd->exec();
	if(cmd->isUndoable()){
		cmdStack.push_back(static_cast <BaseUndoCmd *>(cmd));
	}
}

void CmdManager::undo(){
	ofLogNotice("CmdManager", "undo");
	if(cmdStack.size() > 0){
		BaseUndoCmd * cmd = cmdStack.back();
		cmd->undo();

		// Delete last command now, change this when implementing redo.
		delete cmdStack.back();
		cmdStack.pop_back();
	}else{
		ofLogNotice("CmdManager", "Nothing to undo");
	}
}

} // namespace piMapper
} // namespace ofx