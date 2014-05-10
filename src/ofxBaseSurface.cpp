#include "ofxBaseSurface.h"

ofxBaseSurface::ofxBaseSurface()
{
    ofEnableNormalizedTexCoords();
    createDefaultTexture();
}

void ofxBaseSurface::createDefaultTexture()
{
    ofPixels pixels;
    pixels.allocate(500, 500, 1);
    for ( int i=0; i<pixels.size(); i++ ) {
        pixels[i] = 255;
    }
    int squareSize = 10; // size of each test pattern square
    bool sy = false;
    for ( int y=0; y<pixels.getWidth(); y+=squareSize ) {
        bool sx = false;
        for ( int x=0; x<pixels.getHeight(); x+=squareSize ) {
            for ( int yi=0; yi<squareSize; yi++ ) {
                for ( int xi=0; xi<squareSize; xi++ ){
                    if ( sx && sy ) pixels[(y+yi)*pixels.getWidth()+x+xi] = 255;
                    else if ( sx && !sy ) pixels[(y+yi)*pixels.getWidth()+x+xi] = 0;
                    else if ( !sx && sy ) pixels[(y+yi)*pixels.getWidth()+x+xi] = 0;
                    else pixels[(y+yi)*pixels.getWidth()+x+xi] = 255;
                }
            }
            sx = !sx;
        }
        sy = !sy;
    }
    
    // load pixels into texture
    defaultTexture.loadData(pixels);
    
    // Assign default texture to texture pointer
    texture = &defaultTexture;
}

ofTexture* ofxBaseSurface::getTexture()
{
    return texture;
}