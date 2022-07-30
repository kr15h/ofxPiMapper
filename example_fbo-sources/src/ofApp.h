#pragma once

#include "ofMain.h"
#include "ofxPiMapper.h"
#include "VideoSource.h"
#include "ScanlineSource.h"
#include "CircleSource.h"
#include "QuadSource.h"
#include "BrickSource.h"
//#include "SyphonSource.h"
#include "magSlideShowSource.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);

    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseDragged(int x, int y, int button);

    ofxPiMapper piMapper;

    // By using a custom source that is derived from FboSource
    // you will be able to see the source listed in sources editor
    ScanlineSource ScanLSource;
    QuadSource QuadiSource;
    CircleSource CircLSource;
    BrickSource BricksSource;
    //SyphonSource SyphonClient;
    magSlideShowSource slideShowSource;

};
