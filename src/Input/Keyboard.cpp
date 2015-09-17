#include "Keyboard.h"

namespace ofx {
    namespace piMapper {
    
        Keyboard::Keyboard(ofxPiMapper * opm) {
            _ofxPiMapper = opm;
            ofLogNotice("Keyboard event handler");
            ofAddListener(ofEvents().keyPressed, this, &Keyboard::onKeyPressed);
        }
        
        Keyboard::~Keyboard() {
            _ofxPiMapper = 0;
            ofRemoveListener(ofEvents().keyPressed, this, &Keyboard::onKeyPressed);
        }
        
        void Keyboard::onKeyPressed(ofKeyEventArgs & args) {
            ofLogNotice("Keyboard::onKeyPressed");
            ofLog() << args.keycode;
            
            // Choose what command to create here
            // depending on the key pressed
            switch (args.key) {
                case '1':
                    ofLogNotice("Keyboard::onKeyPressed") << "1";
                    if (_ofxPiMapper->getGui().getMode() != ofx::piMapper::GuiMode::NONE) {
                        _ofxPiMapper->getCmdManager().exec(
                            new ofx::piMapper::SetGuiModeCmd(&_ofxPiMapper->getGui(),
                            ofx::piMapper::GuiMode::NONE));
                    }
                    break;
                case '2':
                    ofLogNotice("Keyboard::onKeyPressed") << "2";
                    if (_ofxPiMapper->getGui().getMode() != ofx::piMapper::GuiMode::PROJECTION_MAPPING) {
                        _ofxPiMapper->getCmdManager().exec(new ofx::piMapper::SetGuiModeCmd(
                        &_ofxPiMapper->getGui(),
                        ofx::piMapper::GuiMode::PROJECTION_MAPPING));
                    }
                    break;
                case '3':
                    ofLogNotice("Keyboard::onKeyPressed") << "3";
                    if (_ofxPiMapper->getGui().getMode() != ofx::piMapper::GuiMode::SOURCE_SELECTION) {
                        _ofxPiMapper->getCmdManager().exec(new ofx::piMapper::SetGuiModeCmd(
                        &_ofxPiMapper->getGui(),
                        ofx::piMapper::GuiMode::SOURCE_SELECTION));
                    }
                    break;
                case '4':
                    ofLogNotice("Keyboard::onKeyPressed") << "4";
                    if (_ofxPiMapper->getGui().getMode() != ofx::piMapper::GuiMode::TEXTURE_MAPPING) {
                        _ofxPiMapper->getCmdManager().exec(new ofx::piMapper::SetGuiModeCmd(
                        &_ofxPiMapper->getGui(),
                        ofx::piMapper::GuiMode::TEXTURE_MAPPING));
                    }
                    break;
                default:
                    // TODO: Forward it to the application state for it to decide.
                    ofLogNotice("Keyboard::onKeyPressed") << "default case";
                    break;
            }
        }
    
    }
}