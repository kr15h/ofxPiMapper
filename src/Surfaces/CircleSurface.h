//
// CircleSurface.h
// Copyright (c) 2017 Cristobal Mendoza
// http://cuppetellimendoza.com

#ifndef OFXPIMAPPER_CIRCLESURFACE_H
#define OFXPIMAPPER_CIRCLESURFACE_H

#include "QuadSurface.h"

#define STRINGIFY(A) #A

namespace ofx {
namespace piMapper {

class CircleSurface : public QuadSurface {
	public:
		CircleSurface();
		CircleSurface(QuadSurface &surface);
		int getType() override;
		~CircleSurface();
		void draw() override;
		void setup() override;

		// TODO: Feathering
		void setFeathering(float f);

	protected:
		void setupTextures();
		ofFbo maskFbo;
		ofFbo scaledSourceFbo;
		ofFbo outputFbo;
		ofShader maskShader;
		ofShader gradientShader;
		float feathering = 0.0f;
		bool updateMask;
		bool maskIsReady;

		string glESFragmentShader;
		string glESVertexShader;

		string gl2FragmentShader;
		string gl2VertexShader;

		ofMesh maskMesh;

		// TODO: gl3 Shaders
//		string          gl3VertexShader;
//		string          gl3FragmentShader;

	private:
		std::vector<ofVec2f> defaultTexCoords;
		// We will use this pointer to determine if the source has changed.
		// This is a total kludge, but it keeps me from messing with the
		// upstream source.
		BaseSource* currentSource = 0;
};

}
}


#endif //OFXPIMAPPER_CIRCLESURFACE_H
