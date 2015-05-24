#include "ViewState.h"

namespace ofx {
    namespace piMapper {
        void ViewState::mousePressed(ofMouseEventArgs & args) { }
        void ViewState::setState(MainView * view, ViewState * state) {
            view->setState(state);
        }
    }
}