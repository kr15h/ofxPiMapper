#pragma once

#include "ofxPiMapper.h"
#include "BaseCmd.h"
#include "SurfaceType.h"
#include "BaseSurface.h"
#include "SurfaceFactory.h"

class ofxPiMapper;

namespace ofx {
namespace piMapper {

class AddSurfaceCmd : public BaseUndoCmd {

	public:
		AddSurfaceCmd(ofxPiMapper * app, int surfaceType);
		void exec();
		void undo();

	private:
		ofxPiMapper * _app;
		int _surfaceType;

		// TODO: Should use some kind of factory class here
		void addTriangleSurface();
		void addQuadSurface();

};

} // namespace piMapper
} // namespace ofx

