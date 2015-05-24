#include "MainView.h"

namespace ofx {
    namespace piMapper {
        MainView::MainView(){ // MainView::MainView(MainController * mainController)
            ofLogNotice("MainView::MainView");
            
            // Init connection with the main controller maybe?
            // _mainController = mainController;
            
            // Init main state
            setState(PresentationViewState::instance());
        }
        
        void MainView::mousePressed(ofMouseEventArgs & args){
            ofLogNotice("MainView::mousePressed");
            _state->mousePressed(args);
        }
        
        void MainView::setState(ofx::piMapper::ViewState * state){
            ofLogNotice("MainView::setState");
            _state = state;
        }
    }
}