#include "CommandManager.h"

namespace ofx{
    namespace piMapper{
        
        void CommandManager::executeCommand(BaseCommand * cmd){
            cmd->execute();
            if (cmd->isUndoable()){
                commandStack.push_back(static_cast<BaseUndoableCommand *>(cmd));
            }
        }
        
        void CommandManager::undo(){
            if (commandStack.size() > 0){
                BaseUndoableCommand * cmd = commandStack.back();
                cmd->undo();
                
                // Delete last command for now
                // TODO: Enable redo func and that means we do not destroy last command,
                //       we move the stack pointer instead.
                delete commandStack.back();
                commandStack.pop_back();
            }
        }
        
    } // namespace piMapper
} // namespace ofx