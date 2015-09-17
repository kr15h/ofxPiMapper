#include "ViewState.h"
#include "PresentationViewState.h"

namespace ofx {
    namespace piMapper {
    
        void ViewState::setState(MainView * mv, ViewState * st) {
            mv->setState(st);
        }
        
    } // namespace piMapper
} // namespace ofx
