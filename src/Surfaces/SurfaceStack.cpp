#include "SurfaceStack.h"

namespace ofx {
namespace piMapper {

void SurfaceStack::push_back(BaseSurface * s){
	ofAddListener(s->verticesChangedEvent, this, &SurfaceStack::onVerticesChanged);
	ofAddListener(s->vertexChangedEvent, this, &SurfaceStack::onVertexChanged);
	_surfaces.push_back(s);
}

void SurfaceStack::pop_back(){
	ofRemoveListener(_surfaces.back()->verticesChangedEvent, this, &SurfaceStack::onVerticesChanged);
	ofRemoveListener(_surfaces.back()->vertexChangedEvent, this, &SurfaceStack::onVertexChanged);
	_surfaces.pop_back();
}

void SurfaceStack::erase(int i){
	ofRemoveListener(_surfaces[i]->verticesChangedEvent, this, &SurfaceStack::onVerticesChanged);
	ofRemoveListener(_surfaces[i]->vertexChangedEvent, this, &SurfaceStack::onVertexChanged);
	_surfaces.erase(_surfaces.begin() + i);
}

void SurfaceStack::swap(int a, int b){
	std::swap(_surfaces[a], _surfaces[b]);
}

void SurfaceStack::draw(){
	for(int i = 0; i < _surfaces.size(); ++i){
		if(_surfaces[i]->getSource()->getType() == SourceType::SOURCE_TYPE_FBO){
			glEnable(GL_BLEND);
			glBlendFuncSeparate(GL_ONE, GL_ZERO, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		}else{
			ofEnableAlphaBlending();
		}
		
		_surfaces[i]->draw();
	}
}

void SurfaceStack::clear(){
	for(int i = 0; i < size(); ++i){
		ofRemoveListener(_surfaces[i]->verticesChangedEvent, this, &SurfaceStack::onVerticesChanged);
		ofRemoveListener(_surfaces[i]->vertexChangedEvent, this, &SurfaceStack::onVertexChanged);
	}
	_surfaces.clear();
}

int SurfaceStack::size(){
	return _surfaces.size();
}

BaseSurface * SurfaceStack::operator[](int i){
	return at(i);
}

BaseSurface * SurfaceStack::at(int i){
	if(i >= _surfaces.size()){
		throw runtime_error("SurfaceStack index out of bounds");
	}
	return _surfaces[i];
}

BaseSurface * SurfaceStack::back(){
	return _surfaces.back();
}

void SurfaceStack::onVerticesChanged(vector<ofVec3f> & vertices){
	ofNotifyEvent(verticesChangedEvent, vertices, this);
}

void SurfaceStack::onVertexChanged(int & i){
	ofNotifyEvent(vertexChangedEvent, i, this);
}

SurfaceStack * SurfaceStack::clone(){
	SurfaceStack * stack = new SurfaceStack();
	for(unsigned int i = 0; i < _surfaces.size(); ++i){
		BaseSurface * surface = _surfaces[i]->clone();
		stack->push_back(surface);
	}
	return stack;
}

} // namespace piMapper
} // namespace ofx
