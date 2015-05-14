#include "CommandManager.h"

namespace ofx{
    namespace piMapper{
        
        void CommandManager::exec(BaseCommand * cmd){
            cmd->exec();
            if (cmd->isUndoable()){
                commandStack.push_back(static_cast<BaseUndoableCommand *>(cmd));
            }
        }
        
        void CommandManager::undo(){
            if (commandStack.size() > 0){
                BaseUndoableCommand * cmd = commandStack.back();
                cmd->undo();
                
                // Delete last command now, change this when implementing redo.
                delete commandStack.back();
                commandStack.pop_back();
            } else {
                ofLogNotice("CommandManager", "Nothing to undo");
            }
        }
        
    } // namespace piMapper
} // namespace ofx