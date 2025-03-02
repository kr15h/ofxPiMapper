#include "ofApp.h"

void ofApp::setup(){
	ofBackground(0);
	//ofSetFrameRate(30);
	//ofSetVerticalSync(false);

	getXWindowNames();

	piMapper.setup();
	
	ofSetFullscreen(false);
	ofSetFullscreen(true);

	ofSetEscapeQuitsApp(false);

}

void ofApp::update(){
	piMapper.update();
}

void ofApp::draw(){
    piMapper.draw();
}

void ofApp::keyPressed(int key){
	piMapper.keyPressed(key);
}

void ofApp::keyReleased(int key){
	piMapper.keyReleased(key);
}

void ofApp::mousePressed(int x, int y, int button){
	piMapper.mousePressed(x, y, button);
}

void ofApp::mouseReleased(int x, int y, int button){
	piMapper.mouseReleased(x, y, button);
}

void ofApp::mouseDragged(int x, int y, int button){
	piMapper.mouseDragged(x, y, button);
}

void ofApp::getXWindowNames(){
	Display *display = XOpenDisplay(nullptr);
    if (!display) {
        ofLogError("XSource App") << "Cannot open X display";
        return;
    }

	Atom netWmName = XInternAtom(display, "_OB_APP_TITLE", false);
	Atom property = XInternAtom(display, "_NET_CLIENT_LIST", true);
    Atom actualType;
    int actualFormat;
    unsigned long numItems, bytesAfter;
    unsigned char *data = nullptr;
	vector<string> windowNameList;
	std::unordered_map<string, int> nameCounts;

	if (XGetWindowProperty(display, DefaultRootWindow(display), property, 0, 1024, false,
		XA_WINDOW, &actualType, &actualFormat, &numItems, &bytesAfter, &data) == Success && data) {
		Window *windows = (Window *)data;

		ofLog() << "============================";
		ofLog() << "   X11 WINDOWS AVAILABLE";
		ofLog() << "============================";

		for (unsigned long i = 0; i < numItems; i++) {
			// Get window name
			char *name = nullptr;
			XTextProperty prop;
			bool usedXFetchName = false;

			if (XGetTextProperty(display, windows[i], &prop, netWmName) && prop.nitems) {
                name = (char *)prop.value;
            }
			if (!name) {
                XFetchName(display, windows[i], &name);
				usedXFetchName = true;
            }
			
			int count = name ? nameCounts[std::string(name)]++ : 0;
            string uniqueName = name ? std::string(name) + " " + std::to_string(count) : "Unnamed Window " + std::to_string(windows[i]); 
			ofLog() << "Window ID: " << windows[i] << " | Name: " << uniqueName;
			piMapper.registerFboSource(new XSource(display, windows[i], uniqueName));
			windowNameList.push_back(uniqueName);

			if (usedXFetchName && name) {
                XFree(name); // Free only if XFetchName() was used
            } else if (prop.nitems) {
                XFree(prop.value); // Free XGetTextProperty() result
            }

		}
		XFree(data);
	} else {
		ofLogError() << "Failed to get window list from X11.";
	}

	// Cleanup
	XCloseDisplay(display);
	filterInvalidSurfaces(windowNameList);
}

void ofApp::filterInvalidSurfaces(const vector<string>& windowNameList) {
    ofxXmlSettings xml;
    if (!xml.load(PIMAPPER_SETTINGS_FILE)) {
        ofLogError() << "Failed to load " << PIMAPPER_SETTINGS_FILE;
        return;
    }

    xml.pushTag("surfaces");
    int numSurfaces = xml.getNumTags("surface");

    for (int i = numSurfaces - 1; i >= 0; --i) {  // Iterate backwards to allow deletion
        xml.pushTag("surface", i);
        std::string sourceName = xml.getValue("source:source-name", "");

        bool removeSurface = std::find(windowNameList.begin(), windowNameList.end(), sourceName) == windowNameList.end();

        xml.popTag();  // Exit "surface" tag before removing
        
        if (removeSurface) {
            xml.removeTag("surface", i);
        }
    }

    xml.popTag();  // Exit "surfaces" tag
    xml.save(PIMAPPER_SETTINGS_FILE);
}
