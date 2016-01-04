#include "SurfaceStack.h"

namespace ofx {
namespace piMapper {

SurfaceStack::SurfaceStack(){}

void SurfaceStack::push_back(BaseSurface * s){
	_surfaces.push_back(s);
}

void SurfaceStack::erase(int i){
	delete _surfaces[i];
	_surfaces.erase(_surfaces.begin() + i);
}

void SurfaceStack::swap(int a, int b){
	std::swap(_surfaces[a], _surfaces[b]);
}

void SurfaceStack::draw(){
	for(int i = 0; i < _surfaces.size(); ++i){
		_surfaces[i]->draw();
	}
}

int SurfaceStack::size(){
	return _surfaces.size();
}

BaseSurface * SurfaceStack::operator[](int i){
	if(i >= _surfaces.size()){
		throw runtime_error("SurfaceStack index out of bounds");
	}
	return _surfaces[i];
}

} // namespace piMapper
} // namespace ofx