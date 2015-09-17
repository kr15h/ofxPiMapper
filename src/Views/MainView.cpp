#include "MainView.h"
#include "PresentationViewState.h"

namespace ofx {
    namespace piMapper {
        
        MainView::MainView(){
            setState(PresentationViewState::instance());
        }
        
        void MainView::draw(){
            _state->draw(this);
        }
        
        void MainView::setState(ViewState * st){
            _state = st;
        }
        
    } // namespace piMapper
} // namespace ofx
