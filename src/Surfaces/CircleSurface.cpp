//
// CircleSurface.cpp
// Copyright (c) 2017 Cristobal Mendoza
// http://cuppetellimendoza.com

#include "CircleSurface.h"

namespace ofx {
namespace piMapper {

CircleSurface::CircleSurface() : QuadSurface() {
	setup();
}

CircleSurface::CircleSurface(QuadSurface &surface) {
	setup();
	setVertices(surface.getVertices());
	setTexCoords(surface.getTexCoords());
	setPerspectiveWarping(surface.getPerspectiveWarping());
}

CircleSurface::~CircleSurface() {}

void CircleSurface::setup() {

	QuadSurface::setup();
	setPerspectiveWarping(true);

	updateMask = true;
//	maskIsReady = false;

	glESVertexShader = CIRCLE_SURFACE_STRINGIFY(
			attribute vec4 position;
			attribute vec4 color;
			attribute vec4 normal;
			attribute vec2 texcoord;

			uniform mat4 modelViewMatrix;
			uniform mat4 projectionMatrix;
			uniform sampler2D maskTex;

			varying vec4 colorVarying;
			varying vec2 texCoordVarying;

			void main() {

				//get our current vertex position so we can modify it
				vec4 pos = projectionMatrix*modelViewMatrix*position;

				gl_Position = pos;
				colorVarying = color;
				texCoordVarying = texcoord;
			}
	);

	glESFragmentShader = CIRCLE_SURFACE_STRINGIFY(
//#ifdef GL_ES
// define default precision for float, vec, mat.
			precision highp float;
//#endif

			uniform sampler2D tex0;
			uniform sampler2D maskTex;
			uniform vec4 globalColor;

			varying vec2 texCoordVarying;

			void main (void)
			{
				vec2 pos = texCoordVarying;
				vec3 src = texture2D(tex0, pos).rgb;
				float mask = texture2D(maskTex, pos).r;
				gl_FragColor = vec4( src , mask);
			}
	);

	gl2FragmentShader = "#version 120\n #extension GL_ARB_texture_rectangle : enable\n";
	gl2FragmentShader += CIRCLE_SURFACE_STRINGIFY(
			uniform sampler2DRect tex0;
			uniform sampler2DRect maskTex;

			void main (void) {
				vec2 pos = gl_TexCoord[0].st;

				vec3 src = texture2DRect(tex0, pos).rgb;
				float mask = texture2DRect(maskTex, pos).r;

				gl_FragColor = vec4(src, mask);
			}
	);

#ifdef TARGET_OPENGLES
	maskShader.setupShaderFromSource(GL_VERTEX_SHADER, glESVertexShader);
	maskShader.setupShaderFromSource(GL_FRAGMENT_SHADER, glESFragmentShader);
	maskShader.bindDefaults();
	maskShader.linkProgram();
#else
	if (ofIsGLProgrammableRenderer()) {

	} else {
		maskShader.setupShaderFromSource(GL_FRAGMENT_SHADER, gl2FragmentShader);
		maskShader.linkProgram();
	}
#endif

	ofVec2f t1 = ofVec2f(ofVec2f(0.0f, 0.0f));
	ofVec2f t2 = ofVec2f(ofVec2f(1.0f, 0.0f));
	ofVec2f t3 = ofVec2f(ofVec2f(1.0f, 1.0f));
	ofVec2f t4 = ofVec2f(ofVec2f(0.0f, 1.0f));

	defaultTexCoords.push_back(t1);
	defaultTexCoords.push_back(t2);
	defaultTexCoords.push_back(t3);
	defaultTexCoords.push_back(t4);
}

void CircleSurface::draw() {

	ofEnableAlphaBlending();
	if (source->getTexture() == 0)
	{
		return;
	}
	if (!source->getTexture()->isAllocated()){
		return;
	}

	if (source != currentSource) { // Pointer comparison
		// Create the mask here
		setupTextures();
		currentSource = source;
	}


	// Save Normie state:
	auto isNorm = ofGetUsingNormalizedTexCoords();

	// If we get to this part of the function, the mask fbo
	// should already be allocated and the mask texture created.

	ofEnableNormalizedTexCoords();
	// Get the texture from the source an store a copy
	// of the source texture's id:
	auto sourceTex = ofTexture(*(source->getTexture()));
	auto sourceTexId = sourceTex.getTextureData().textureID;

	// Get the quad surface's mesh texture coordinates:
	auto quadTexCoords = getMesh().getTexCoords();

	maskMesh.clearTexCoords();

	// Set the mesh's texture coords to the quads.
	// This gets us the coordinates set in the TextureEditor
	maskMesh.addTexCoords(quadTexCoords);

	float w = outputFbo.getWidth();
	float h = outputFbo.getHeight();

	// Draw the scaled texture into an FBO
	scaledSourceFbo.begin(true);
	{
		ofClear(0, 0, 0, 255);
		ofSetupScreenOrtho(w, h, -1, 1);
		ofEnableNormalizedTexCoords();
		ofFill();
		ofSetColor(255);
		sourceTex.bind();
		maskMesh.draw();
		sourceTex.unbind();
	}
	scaledSourceFbo.end();

	// Now draw the texture, masked, into the outputFbo.
	// This enables us to use the TextureEditor to determine
	// what part of the source will be masked:
	maskMesh.clearTexCoords();

	// Set default normalized texCoords
	maskMesh.addTexCoords(defaultTexCoords);

	outputFbo.begin(true);
	{
		ofClear(0, 0, 0, 0);
		ofSetupScreenOrtho(w, h, -1, 1);
		ofEnableNormalizedTexCoords();
		ofSetColor(255);
		ofFill();
		ofSetRectMode(OF_RECTMODE_CORNER);
#ifdef TARGET_RASPBERRY_PI
		scaledSourceFbo.getTexture().bind();
		maskMesh.draw();
		scaledSourceFbo.getTexture().unbind();

		// Masking without shaders...
		ofPushStyle();
		ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
		ofSetColor(255);
		ofFill();
		ofDisableNormalizedTexCoords();
		maskFbo.draw(0, 0);
		ofPopStyle();
#else
		maskShader.begin();
		maskShader.setUniformTexture("maskTex", maskFbo.getTexture(), 1);
		ofSetColor(255);
		ofFill();
		ofSetRectMode(OF_RECTMODE_CORNER);
		scaledSourceFbo.getTexture().bind();
		maskMesh.draw();
		scaledSourceFbo.getTexture().unbind();
		maskShader.end();
#endif

	}
	outputFbo.end();

	getMesh().clearTexCoords();
	getMesh().addTexCoords(defaultTexCoords);

	// Swap the texture id of the source with the one of our
	// newly drawn outputFbo:
	source->getTexture()->getTextureData().textureID = outputFbo.getTexture().getTextureData().textureID;

	// Draw the Quad:
	QuadSurface::draw();

	// Reset the texture id of the source
	source->getTexture()->getTextureData().textureID = sourceTexId;

	// Reset the texture coords of the QuadSurface mesh:
	getMesh().clearTexCoords();
	getMesh().addTexCoords(quadTexCoords);

	if (!isNorm) ofDisableNormalizedTexCoords();
}

void CircleSurface::setFeathering(float f) {
	feathering = f;
	updateMask = true;
}

void CircleSurface::setupTextures() {
	float w = source->getTexture()->getWidth();
	float h = source->getTexture()->getHeight();
	float dia = 0;
	if (w > h) {
		dia = h;
	} else {
		dia = w;
	}

	float padding = 10;

	maskFbo.allocate(w, h);
	maskFbo.begin(false);
	ofPushStyle();
	ofSetupScreenOrtho(w, h, -1, 1);
	ofClear(0, 0, 0, 255);
	ofFill();
	ofSetColor(255);
	ofSetCircleResolution(300);
	ofDrawEllipse(w/2, h/2, w-padding, h-padding);
	ofPopStyle();
	maskFbo.end();

	outputFbo.allocate(w, h);
	outputFbo.begin();
	ofClear(0, 0, 0, 255);
	outputFbo.end();

	scaledSourceFbo.allocate(w, h);
	scaledSourceFbo.begin();
	ofClear(0, 0, 0, 255);
	scaledSourceFbo.end();

	// This is lifted from QuadSurface::setup to ensure that the two
	// meshes are similar:

	// Create 4 points for the 2 triangles
	ofVec2f p1 = ofVec2f(0, 0);
	ofVec2f p2 = ofVec2f(0, h);
	ofVec2f p3 = ofVec2f(w, h);
	ofVec2f p4 = ofVec2f(w, 0);

	// Create 4 point for the texture coordinates
	ofVec2f t1 = ofVec2f(ofVec2f(0.0f, 0.0f));
	ofVec2f t2 = ofVec2f(ofVec2f(1.0f, 0.0f));
	ofVec2f t3 = ofVec2f(ofVec2f(1.0f, 1.0f));
	ofVec2f t4 = ofVec2f(ofVec2f(0.0f, 1.0f));
	
	// Clear maskMesh
	maskMesh.clear();

	// Create a surface with the points
	maskMesh.addVertex(p1);
	maskMesh.addVertex(p2);
	maskMesh.addVertex(p3);
	maskMesh.addVertex(p4);

	// Add 2 triangles
	maskMesh.addTriangle(0, 2, 3);
	maskMesh.addTriangle(0, 1, 2);

	// Add texture coordinates
	maskMesh.addTexCoord(t1);
	maskMesh.addTexCoord(t2);
	maskMesh.addTexCoord(t3);
	maskMesh.addTexCoord(t4);
}



int CircleSurface::getType() {
	return SurfaceType::CIRCLE_SURFACE;
}

}
}