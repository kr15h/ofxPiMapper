#include "SurfaceManager.h"

namespace ofx {
namespace piMapper {

SurfaceManager::SurfaceManager(){
	mediaServer = 0;
	selectedSurface = 0;
}

SurfaceManager::~SurfaceManager(){
	clear();
}

void SurfaceManager::draw(){
	_surfaces.draw();
}

// Add existing surface
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
	xmlSettings.clear();

	// Save surfaces
	xmlSettings.addTag("surfaces");
	xmlSettings.pushTag("surfaces");
	for(int i = 0; i < _surfaces.size(); i++){
		xmlSettings.addTag("surface");
		xmlSettings.pushTag("surface", i);
		BaseSurface * surface = _surfaces[i];

		xmlSettings.addTag("vertices");
		xmlSettings.pushTag("vertices");
		vector <ofVec3f> * vertices = &surface->getVertices();
		for(int j = 0; j < vertices->size(); j++){
			xmlSettings.addTag("vertex");
			xmlSettings.pushTag("vertex", j);
			ofVec3f * vertex = &(*vertices)[j];
			xmlSettings.addValue("x", vertex->x);
			xmlSettings.addValue("y", vertex->y);

			// we don't need z as it will be 0 anyways

			xmlSettings.popTag(); // vertex
		}
		xmlSettings.popTag(); // vertices

		xmlSettings.addTag("texCoords");
		xmlSettings.pushTag("texCoords");
		vector <ofVec2f> * texCoords = &surface->getTexCoords();
		for(int j = 0; j < texCoords->size(); j++){
			xmlSettings.addTag("texCoord");
			xmlSettings.pushTag("texCoord", j);
			ofVec2f * texCoord = &(*texCoords)[j];
			xmlSettings.addValue("x", texCoord->x);
			xmlSettings.addValue("y", texCoord->y);
			xmlSettings.popTag(); // texCoord
		}
		xmlSettings.popTag(); // texCoords
		xmlSettings.addTag("source");
		xmlSettings.pushTag("source");
		string sourceTypeName = SourceType::GetSourceTypeName(surface->getSource()->getType());
		cout << "sourceTypeName: " << sourceTypeName << endl;
		xmlSettings.addValue("source-type", sourceTypeName);
		xmlSettings.addValue("source-name", surface->getSource()->getName());
		xmlSettings.popTag(); // source
		xmlSettings.popTag(); // surface
	}
	xmlSettings.popTag(); // surfaces
	xmlSettings.save(fileName);
}

bool SurfaceManager::loadXmlSettings(string fileName){

	// Exit if there is no media server
	if(mediaServer == 0){
		ofLogFatalError("SurfaceManager") << "Media server not set";
		exit(EXIT_FAILURE);
	}
	if(!xmlSettings.loadFile(fileName)){
		ofLogWarning("SurfaceManager") << "Could not load XML settings";
		return false;
	}
	if(!xmlSettings.tagExists("surfaces")){
		ofLogWarning("SurfaceManager") << "XML settings is empty or has wrong markup";
		return false;
	}

	xmlSettings.pushTag("surfaces");

	int numSurfaces = xmlSettings.getNumTags("surface");
	for(int i = 0; i < numSurfaces; i++){
		xmlSettings.pushTag("surface", i);

		// attempt to load surface source
		xmlSettings.pushTag("source");
		string sourceType = xmlSettings.getValue("source-type", "");
		string sourceName = xmlSettings.getValue("source-name", "");
		BaseSource * source = 0;
		if(sourceName != "" && sourceName != "none" && sourceType != ""){

			// Load source depending on type
			int typeEnum = SourceType::GetSourceTypeEnum(sourceType);
			if(typeEnum == SourceType::SOURCE_TYPE_FBO){
				// Load FBO source using sourceName
				source = mediaServer->loadMedia(sourceName, typeEnum);
			}else{
				// Construct full path
				string dir = mediaServer->getDefaultMediaDir(typeEnum);
				stringstream pathss;
				pathss << ofToDataPath(dir, true) << sourceName;
				string sourcePath = pathss.str();
				// Load media by using full path
				source = mediaServer->loadMedia(sourcePath, typeEnum);
			}
		}
		xmlSettings.popTag(); // source
		xmlSettings.pushTag("vertices");
		vector <ofVec2f> vertices;
		int vertexCount = xmlSettings.getNumTags("vertex");
		
		if(vertexCount == 3){
			xmlSettings.pushTag("vertex", 0);
			vertices.push_back(ofVec2f(xmlSettings.getValue("x", 0.0f),
									   xmlSettings.getValue("y", 0.0f)));
			xmlSettings.popTag();

			xmlSettings.pushTag("vertex", 1);
			vertices.push_back(ofVec2f(xmlSettings.getValue("x", 100.0f),
									   xmlSettings.getValue("y", 0.0f)));
			xmlSettings.popTag();

			xmlSettings.pushTag("vertex", 2);
			vertices.push_back(ofVec2f(xmlSettings.getValue("x", 0.0f),
									   xmlSettings.getValue("y", 100.0f)));
			xmlSettings.popTag();

			xmlSettings.popTag(); // vertices

			xmlSettings.pushTag("texCoords");

			vector <ofVec2f> texCoords;

			xmlSettings.pushTag("texCoord", 0);
			texCoords.push_back(ofVec2f(xmlSettings.getValue("x", 0.0f),
										xmlSettings.getValue("y", 0.0f)));
			xmlSettings.popTag();

			xmlSettings.pushTag("texCoord", 1);
			texCoords.push_back(ofVec2f(xmlSettings.getValue("x", 1.0f),
										xmlSettings.getValue("y", 0.0f)));
			xmlSettings.popTag();

			xmlSettings.pushTag("texCoord", 2);
			texCoords.push_back(ofVec2f(xmlSettings.getValue("x", 0.0f),
										xmlSettings.getValue("y", 1.0f)));
			xmlSettings.popTag();

			xmlSettings.popTag(); // texCoords

			// Create and add a triangle surface
			BaseSurface * triangleSurface =
				SurfaceFactory::instance()->createSurface(
					SurfaceType::TRIANGLE_SURFACE);
			triangleSurface->setVertices(vertices);
			triangleSurface->setTexCoords(texCoords);
			
			if(sourceName != "none" && source != 0){
				triangleSurface->setSource(source);
			}

			addSurface(triangleSurface);
		
		}else if(vertexCount == 4){
			xmlSettings.pushTag("vertex", 0);
			vertices.push_back(ofVec2f(xmlSettings.getValue("x", 0.0f),
									   xmlSettings.getValue("y", 0.0f)));
			xmlSettings.popTag();

			xmlSettings.pushTag("vertex", 1);
			vertices.push_back(ofVec2f(xmlSettings.getValue("x", 100.0f),
									   xmlSettings.getValue("y", 0.0f)));
			xmlSettings.popTag();

			xmlSettings.pushTag("vertex", 2);
			vertices.push_back(ofVec2f(xmlSettings.getValue("x", 100.0f),
									   xmlSettings.getValue("y", 100.0f)));
			xmlSettings.popTag();

			xmlSettings.pushTag("vertex", 3);
			vertices.push_back(ofVec2f(xmlSettings.getValue("x", 0.0f),
									   xmlSettings.getValue("y", 100.0f)));
			xmlSettings.popTag();

			xmlSettings.popTag(); // vertices

			xmlSettings.pushTag("texCoords");

			vector <ofVec2f> texCoords;

			xmlSettings.pushTag("texCoord", 0);
			texCoords.push_back(ofVec2f(xmlSettings.getValue("x", 0.0f),
										xmlSettings.getValue("y", 0.0f)));
			xmlSettings.popTag();

			xmlSettings.pushTag("texCoord", 1);
			texCoords.push_back(ofVec2f(xmlSettings.getValue("x", 1.0f),
										xmlSettings.getValue("y", 0.0f)));
			xmlSettings.popTag();

			xmlSettings.pushTag("texCoord", 2);
			texCoords.push_back(ofVec2f(xmlSettings.getValue("x", 1.0f),
										xmlSettings.getValue("y", 1.0f)));
			xmlSettings.popTag();

			xmlSettings.pushTag("texCoord", 3);
			texCoords.push_back(ofVec2f(xmlSettings.getValue("x", 0.0f),
										xmlSettings.getValue("y", 1.0f)));
			xmlSettings.popTag();

			xmlSettings.popTag(); // texCoords

			// Create and add quad surface
			BaseSurface * quadSurface =
				SurfaceFactory::instance()->createSurface(
					SurfaceType::QUAD_SURFACE);
			quadSurface->setVertices(vertices);
			quadSurface->setTexCoords(texCoords);
			
			if(sourceName != "none" && source != 0){
				quadSurface->setSource(source);
			}
			
			addSurface(quadSurface);
		}

		xmlSettings.popTag(); // surface
	}

	xmlSettings.popTag(); // surfaces
	
	return true;
}

void SurfaceManager::setMediaServer(MediaServer * newMediaServer){
	mediaServer = newMediaServer;
}

BaseSurface * SurfaceManager::selectSurface(int index){
	if(index >= _surfaces.size()){
		throw runtime_error("Surface index out of bounds.");
	}
	selectedSurface = _surfaces[index];

	// notify that a new surface has been selected
	ofSendMessage("surfaceSelected");
	return selectedSurface;
}

BaseSurface * SurfaceManager::selectSurface(BaseSurface * surface){
	for(int i = 0; i < _surfaces.size(); i++){
		if(_surfaces[i] == surface){
			selectedSurface = surface;
			ofSendMessage("surfaceSelected");
			return selectedSurface;
		}
	}
	
	deselectSurface();
	return 0;
}

BaseSurface * SurfaceManager::getSelectedSurface(){
	return selectedSurface;
}

void SurfaceManager::deselectSurface(){
	selectedSurface = 0;
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

} // namespace piMapper
} // namespace ofx
