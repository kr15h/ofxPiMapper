#include "ofxSourcesEditor.h"

ofxSourcesEditor::ofxSourcesEditor()
{
    defImgDir = DEFAULT_IMAGES_DIR;
    registerAppEvents();
}

ofxSourcesEditor::~ofxSourcesEditor()
{
    unregisterAppEvents();
    delete gui;
    while ( images.size() ) {
        delete images.back();
        images.pop_back();
    }
}

void ofxSourcesEditor::registerAppEvents()
{
    ofAddListener(ofEvents().setup, this, &ofxSourcesEditor::setup);
}

void ofxSourcesEditor::unregisterAppEvents()
{
    ofRemoveListener(ofEvents().setup, this, &ofxSourcesEditor::setup);
}

void ofxSourcesEditor::setup(ofEventArgs& args)
{
    gui = new ofxUICanvas();
    gui->disable();
    gui->disableAppDrawCallback();
    
    // read directory contents
    ofDirectory imgDir;
    imgDir.listDir(defImgDir);
    imgDir.sort();
    
    vector<string> vnames;
    
    for(int i = 0; i < (int)imgDir.size(); i++){
		//images[i].loadImage(imgDir.getPath(i));
        vnames.push_back(imgDir.getName(i));
	}
    
    gui->addLabel(defImgDir, OFX_UI_FONT_SMALL);
    ofxUIRadio *radio = gui->addRadio("images", vnames, OFX_UI_ORIENTATION_VERTICAL);
    radio->activateToggle("image0.png");
    
    ofAddListener(gui->newGUIEvent,this,&ofxSourcesEditor::guiEvent);
}

void ofxSourcesEditor::draw()
{
    gui->draw();
}

void ofxSourcesEditor::loadImage( string name, string path )
{
    images.push_back(new ofImage());
    images.back()->loadImage(path);
    
    imageNames.push_back(name);
    
    ofSendMessage("imageLoaded");
}

void ofxSourcesEditor::disable()
{
    gui->disable();
}

void ofxSourcesEditor::enable()
{
    gui->enable();
}

void ofxSourcesEditor::setSurfaceManager(ofxSurfaceManager *newSurfaceManager)
{
    surfaceManager = newSurfaceManager;
}

int ofxSourcesEditor::getLoadedTexCount()
{
    return images.size();
}

ofTexture* ofxSourcesEditor::getTexture(int index)
{
    if (index >= images.size()){
        throw std::runtime_error("Texture index out of bounds.");
    }
    
    return &images[index]->getTextureReference();
}

void ofxSourcesEditor::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName();
	int kind = e.widget->getKind();
    
    if(kind == OFX_UI_WIDGET_TOGGLE){
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        cout << name << "\t value: " << toggle->getValue() << endl;
    }
    
    if ( surfaceManager->getSelectedSurface() == NULL ) {
        return;
    }
    
    if (name == "images") {
        return;
    }
    
    stringstream ss;
    ss << defImgDir << name;
    cout << "attempt to load image: " << ss.str() << endl;
    ofTexture* texture = surfaceManager->loadImageSource(name, ss.str());
    surfaceManager->getSelectedSurface()->setTexture(texture);
    surfaceManager->manageMemory();
}