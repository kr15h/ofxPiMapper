#include "SurfaceStack.h"

namespace ofx {
namespace piMapper {

SurfaceStack::SurfaceStack(){}

void SurfaceStack::push_back(ofx::piMapper::BaseSurface & s){
	_surfaces.push_back(s);
}

void SurfaceStack::pop_back(){
	if(_surfaces.size() > 0){
		_surfaces.pop_back();
	}
}

int SurfaceStack::size(){
	return _surfaces.size();
}

void SurfaceStack::erase(int pos){
	_surfaces.erase(_surfaces.begin() + pos);
}

void SurfaceStack::swap(ofx::piMapper::BaseSurface * a, ofx::piMapper::BaseSurface * b){
	std::swap(a, b);
}

} // namespace piMapper
} // namespace ofx