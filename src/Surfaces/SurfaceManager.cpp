#include "SurfaceManager.h"

namespace ofx {
namespace piMapper {

SurfaceManager::SurfaceManager(){
	mediaServer = 0;
	selectedSurface = 0;
	ofAddListener(
		SurfaceStack::instance()->vertexChangedEvent,
		this,
		&SurfaceManager::onVertexChanged);
	ofAddListener(
		SurfaceStack::instance()->verticesChangedEvent,
		this,
		&SurfaceManager::onVerticesChanged);
	_selectedVertexIndex = -1;
}

void SurfaceManager::draw(){
	SurfaceStack::instance()->draw();
}

void SurfaceManager::addSurface(BaseSurface * surface){
	SurfaceStack::instance()->push_back(surface);
}

void SurfaceManager::removeSelectedSurface(){
	if(selectedSurface == 0){
		return;
	}
	
	for(int i = 0; i < SurfaceStack::instance()->size(); i++){
		if(SurfaceStack::instance()->at(i) == selectedSurface){
			SurfaceStack::instance()->erase(i);
			selectedSurface = 0;
			_selectedVertexIndex = -1;
			break;
		}
	}
}

void SurfaceManager::removeSurface(){
	if(SurfaceStack::instance()->size() <= 0){
		return;
	}
    BaseSurface * s = SurfaceStack::instance()->back();
	SurfaceStack::instance()->pop_back();
    delete s;
}

void SurfaceManager::deleteSurface(ofx::piMapper::BaseSurface * surface){
	for(int i = 0; i < SurfaceStack::instance()->size(); ++i){
		if(SurfaceStack::instance()->at(i) == surface){
			SurfaceStack::instance()->erase(i);
			break;
		}
	}
}

void SurfaceManager::clear(){
	while(SurfaceStack::instance()->size()){
		delete SurfaceStack::instance()->back();
		SurfaceStack::instance()->pop_back();
	}
}

void SurfaceManager::saveXmlSettings(string fileName){
	if(mediaServer == 0){
		ofLogFatalError("SurfaceManager") << "Media server not set";
		exit(EXIT_FAILURE);
	}
	
	SettingsLoader::instance()->save(*SurfaceStack::instance(), fileName);
}

bool SurfaceManager::loadXmlSettings(string fileName){
	if(mediaServer == 0){
		ofLogFatalError("SurfaceManager") << "Media server not set";
		exit(EXIT_FAILURE);
	}
	
	return SettingsLoader::instance()->load(*SurfaceStack::instance(), *mediaServer, fileName);
}

void SurfaceManager::setMediaServer(MediaServer * newMediaServer){
	mediaServer = newMediaServer;
}

BaseSurface * SurfaceManager::selectSurface(int index){
	if(index >= SurfaceStack::instance()->size()){
		throw runtime_error("Surface index out of bounds.");
	}

	selectedSurface = SurfaceStack::instance()->at(index);
	_selectedVertexIndex = -1;
	ofSendMessage("surfaceSelected");
	return selectedSurface;
}

BaseSurface * SurfaceManager::selectSurface(BaseSurface * surface){
	for(int i = 0; i < SurfaceStack::instance()->size(); i++){
		if(SurfaceStack::instance()->at(i) == surface){
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
	
	for(int i = 0; i < SurfaceStack::instance()->size(); ++i){
		if(SurfaceStack::instance()->at(i) == selectedSurface){
			if(i < SurfaceStack::instance()->size() - 1){
				next = i + 1;
			}else{
				next = 0;
			}
			
			selectedSurface = SurfaceStack::instance()->at(next);
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
		prev = SurfaceStack::instance()->size() - 1;
		selectedSurface = selectSurface(prev);
		ofNotifyEvent(surfaceSelectedEvent, prev, this);
		return selectedSurface;
	}
	
	for(int i = 0; i < SurfaceStack::instance()->size(); ++i){
		if(SurfaceStack::instance()->at(i) == selectedSurface){
			if(i > 0){
				prev = i - 1;
			}else{
				prev = SurfaceStack::instance()->size() - 1;
			}
			
			selectedSurface = SurfaceStack::instance()->at(prev);
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
	for(int i = 0; i < SurfaceStack::instance()->size(); ++i){
		SurfaceStack::instance()->at(i)->moveBy(v);
	}
}

void SurfaceManager::deselectSurface(){
	selectedSurface = 0;
	_selectedVertexIndex = -1;
}

BaseSurface * SurfaceManager::getSurface(int index){
	if(index >= SurfaceStack::instance()->size()){
		throw runtime_error("Surface index out of bounds.");
		return 0;
	}
	
	return SurfaceStack::instance()->at(index);
}

int SurfaceManager::size(){
	return SurfaceStack::instance()->size();
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
