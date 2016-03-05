#include "SurfaceManager.h"

namespace ofx {
namespace piMapper {

SurfaceManager::SurfaceManager(){
	mediaServer = 0;
	selectedSurface = 0;
	ofAddListener(_surfaces.vertexChangedEvent, this, &SurfaceManager::onVertexChanged);
	ofAddListener(_surfaces.verticesChangedEvent, this, &SurfaceManager::onVerticesChanged);
	_selectedVertexIndex = -1;
}

void SurfaceManager::draw(){
	_surfaces.draw();
}

void SurfaceManager::addSurface(BaseSurface * surface){
	_surfaces.push_back(surface);
}

void SurfaceManager::removeSelectedSurface(){
	if(selectedSurface == 0){
		return;
	}
	
	for(int i = 0; i < _surfaces.size(); i++){
		if(_surfaces[i] == selectedSurface){
			_surfaces.erase(i);
			selectedSurface = 0;
			_selectedVertexIndex = -1;
			break;
		}
	}
}

void SurfaceManager::removeSurface(){
	if(_surfaces.size() <= 0){
		return;
	}
	delete _surfaces.back();
	_surfaces.pop_back();
}

void SurfaceManager::deleteSurface(ofx::piMapper::BaseSurface * surface){
	for(int i = 0; i < _surfaces.size(); ++i){
		if(_surfaces[i] == surface){
			_surfaces.erase(i);
			break;
		}
	}
}

void SurfaceManager::clear(){
	while(_surfaces.size()){
		delete _surfaces.back();
		_surfaces.pop_back();
	}
}

void SurfaceManager::saveXmlSettings(string fileName){
	if(mediaServer == 0){
		ofLogFatalError("SurfaceManager") << "Media server not set";
		exit(EXIT_FAILURE);
	}
	
	SettingsLoader::instance()->save(_surfaces, fileName);
}

bool SurfaceManager::loadXmlSettings(string fileName){
	if(mediaServer == 0){
		ofLogFatalError("SurfaceManager") << "Media server not set";
		exit(EXIT_FAILURE);
	}
	
	return SettingsLoader::instance()->load(_surfaces, *mediaServer, fileName);
}

void SurfaceManager::setMediaServer(MediaServer * newMediaServer){
	mediaServer = newMediaServer;
}

BaseSurface * SurfaceManager::selectSurface(int index){
	if(index >= _surfaces.size()){
		throw runtime_error("Surface index out of bounds.");
	}

	selectedSurface = _surfaces[index];
	_selectedVertexIndex = -1;
	ofSendMessage("surfaceSelected");
	return selectedSurface;
}

BaseSurface * SurfaceManager::selectSurface(BaseSurface * surface){
	for(int i = 0; i < _surfaces.size(); i++){
		if(_surfaces[i] == surface){
			selectedSurface = surface;
			_selectedVertexIndex = -1;
			ofSendMessage("surfaceSelected");
			ofNotifyEvent(surfaceSelectedEvent, i, this);
			return selectedSurface;
		}
	}
	
	deselectSurface();
	return 0;
}

BaseSurface * SurfaceManager::selectNextSurface(){
	int next;
	_selectedVertexIndex = -1;
	
	if(selectedSurface == 0){
		next = 0;
		selectedSurface = selectSurface(next);
		ofNotifyEvent(surfaceSelectedEvent, next, this);
		return selectedSurface;
	}
	
	for(int i = 0; i < _surfaces.size(); ++i){
		if(_surfaces[i] == selectedSurface){
			if(i < _surfaces.size() - 1){
				next = i + 1;
			}else{
				next = 0;
			}
			
			selectedSurface = _surfaces[next];
			ofNotifyEvent(surfaceSelectedEvent, next, this);
			return selectedSurface;
		}
	}
	
	return 0;
}

BaseSurface * SurfaceManager::selectPrevSurface(){
	int prev;
	_selectedVertexIndex = -1;
	
	if(selectedSurface == 0){
		prev = _surfaces.size() - 1;
		selectedSurface = selectSurface(prev);
		ofNotifyEvent(surfaceSelectedEvent, prev, this);
		return selectedSurface;
	}
	
	for(int i = 0; i < _surfaces.size(); ++i){
		if(_surfaces[i] == selectedSurface){
			if(i > 0){
				prev = i - 1;
			}else{
				prev = _surfaces.size() - 1;
			}
			
			selectedSurface = _surfaces[prev];
			ofNotifyEvent(surfaceSelectedEvent, prev, this);
			return selectedSurface;
		}
	}
	
	return 0;
}

BaseSurface * SurfaceManager::getSelectedSurface(){
	return selectedSurface;
}

// TODO: select vertex should be implemented ad BaseSurface level
void SurfaceManager::selectNextVertex(){
	if(selectedSurface == 0){
		return;
	}
	
	int numVertices = selectedSurface->getVertices().size();
	
	if(_selectedVertexIndex == -1){
		_selectedVertexIndex = 0;
	}else if(_selectedVertexIndex < numVertices - 1){
		_selectedVertexIndex += 1;
	}else{
		_selectedVertexIndex = 0;
	}
	
	ofNotifyEvent(vertexSelectedEvent, _selectedVertexIndex, this);
}

// TODO: select vertex should be implemented at BaseSurface level
void SurfaceManager::selectPrevVertex(){
	if(selectedSurface == 0){
		return;
	}
	
	int numVertices = selectedSurface->getVertices().size();
	
	if(_selectedVertexIndex > 0){
		_selectedVertexIndex -= 1;
	}else{
		_selectedVertexIndex = numVertices - 1;
	}
	
	ofNotifyEvent(vertexSelectedEvent, _selectedVertexIndex, this);
}

void SurfaceManager::selectVertex(int i){
	if(selectedSurface == 0){
		return;
	}
	
	if(i > selectedSurface->getVertices().size() - 1){
		ofLogError("SurfaceManager::selectVertex") << "index (" << i << ") out of bounds" << endl;
		int prevVertIndex = _selectedVertexIndex;
		ofNotifyEvent(vertexUnselectedEvent, prevVertIndex, this);
		_selectedVertexIndex = -1;
		return;
	}
	
	_selectedVertexIndex = i;
	ofNotifyEvent(vertexSelectedEvent, _selectedVertexIndex, this);
}

void SurfaceManager::moveSelectionBy(ofVec2f v){
	if(selectedSurface == 0){
		moveAllSurfacesBy(v);
		return;
	}
	
	if(_selectedVertexIndex != -1){
		selectedSurface->getVertices()[_selectedVertexIndex] += v;
		ofNotifyEvent(vertexChangedEvent, _selectedVertexIndex, this);
	}else{
		selectedSurface->moveBy(v);
	}
	
	// TODO: instead of having single selected surface
	// we want to have a selection of one or more.
	// it could be implemented as vector here.
}

void SurfaceManager::moveAllSurfacesBy(ofVec2f v){
	for(int i = 0; i < _surfaces.size(); ++i){
		_surfaces[i]->moveBy(v);
	}
}

void SurfaceManager::deselectSurface(){
	selectedSurface = 0;
	_selectedVertexIndex = -1;
}

BaseSurface * SurfaceManager::getSurface(int index){
	if(index >= _surfaces.size()){
		throw runtime_error("Surface index out of bounds.");
		return 0;
	}
	
	return _surfaces[index];
}

int SurfaceManager::size(){
	return _surfaces.size();
}

int SurfaceManager::getSelectedVertexIndex(){
	return _selectedVertexIndex;
}

void SurfaceManager::onVertexChanged(int & i){
	ofNotifyEvent(vertexChangedEvent, i, this);
}

void SurfaceManager::onVerticesChanged(vector<ofVec3f> & vertices){
	ofNotifyEvent(verticesChangedEvent, vertices, this);
}

} // namespace piMapper
} // namespace ofx
