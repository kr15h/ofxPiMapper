#include "MvSelectionCmd.h"

namespace ofx {
namespace piMapper {

MvSelectionCmd::MvSelectionCmd(SurfaceManager * sm, ofVec2f moveBy){
	_surfaceManager = sm;
	_movedBy = moveBy;
}

void MvSelectionCmd::exec(){
	ofLogNotice("MvSelectionCmd", "exec");
	_surfaceManager->moveSelectionBy(_movedBy);
}

void MvSelectionCmd::undo(){
	ofLogNotice("MvSelectionCmd", "undo");
	_surfaceManager->moveSelectionBy(-_movedBy);
}

} // namespace piMapper
} // namespace ofx

