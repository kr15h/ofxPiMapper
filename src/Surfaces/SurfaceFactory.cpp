#include "SurfaceFactory.h"

namespace ofx {
namespace piMapper {

SurfaceFactory * SurfaceFactory::_instance = 0;

SurfaceFactory * SurfaceFactory::instance(){
	if(_instance == 0){
		_instance = new ofx::piMapper::SurfaceFactory();
	}
	return _instance;
}

BaseSurface * SurfaceFactory::createSurface(int type){
	if(type == SurfaceType::TRIANGLE_SURFACE){
		// TODO: Create triangle surface
	}else if(type == SurfaceType::QUAD_SURFACE){
		// TODO: Create quad surface
	}else{
		throw runtime_error("Undefined surface type");
	}
}

} // namespace piMapper
} // namespace ofx
