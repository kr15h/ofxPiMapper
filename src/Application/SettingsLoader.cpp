#include "SettingsLoader.h"

namespace ofx {
namespace piMapper {

// TODO: Figure out how to solve readability regarding
//       xmlSettings->pushTag() and xmlSettings->popTag()

SettingsLoader * SettingsLoader::_instance = 0;

SettingsLoader * SettingsLoader::instance(){
	if(_instance == 0){
		_instance = new ofx::piMapper::SettingsLoader();
	}
	return _instance;
}

bool SettingsLoader::load(SurfaceStack & surfaces, MediaServer & mediaServer, string fileName){
	
	ofxXmlSettings * xmlSettings = new ofxXmlSettings();
	string sourceType = "";
	string sourceName = "";
	
	BaseSource * source = 0;
	
	if(!xmlSettings->loadFile(fileName)){
		ofLogWarning("SettingsLoader::load()") << "Could not load XML settings";
		return false;
	}
	
	if(!xmlSettings->tagExists("surfaces")){
		ofLogWarning("SettingsLoader::load()") << "XML settings is empty or has wrong markup";
		return false;
	}else{
		xmlSettings->pushTag("surfaces");

		int numSurfaces = xmlSettings->getNumTags("surface");
		for(int i = 0; i < numSurfaces; i++){
			if(xmlSettings->tagExists("surface", i)){
				xmlSettings->pushTag("surface", i);

				// attempt to load surface source
				if(xmlSettings->tagExists("source", 0)){
					xmlSettings->pushTag("source");
					sourceType = xmlSettings->getValue("source-type", "");
					sourceName = xmlSettings->getValue("source-name", "");
					
					if(sourceName != "" && sourceName != "none" && sourceType != ""){

						// Load source depending on type
						int typeEnum = SourceType::GetSourceTypeEnum(sourceType);
						if(typeEnum == SourceType::SOURCE_TYPE_FBO){
				
							// Load FBO source using sourceName
							source = mediaServer.loadMedia(sourceName, typeEnum);
						}else{
				
							// Construct full path
							string dir = mediaServer.getDefaultMediaDir(typeEnum);
							stringstream pathss;
							pathss << ofToDataPath(dir, true) << sourceName;
							string sourcePath = pathss.str();
				
							// Load media by using full path
							source = mediaServer.loadMedia(sourcePath, typeEnum);
						}
					}
		
					xmlSettings->popTag(); // source
				}
				
				if(xmlSettings->tagExists("vertices", 0)){
					xmlSettings->pushTag("vertices");
					int vertexCount = xmlSettings->getNumTags("vertex");
		
					if(vertexCount == 3){
						BaseSurface * triangleSurface = getTriangleSurface(xmlSettings);
						if(sourceName != "none" && source != 0){
							triangleSurface->setSource(source);
						}
						surfaces.push_back(triangleSurface);
					}else if(vertexCount == 4){
						BaseSurface * quadSurface = getQuadSurface(xmlSettings);
						if(sourceName != "none" && source != 0){
							quadSurface->setSource(source);
						}
						surfaces.push_back(quadSurface);
					}
					
					//xmlSettings->popTag(); // vertices
					// this is done in getTriangleSurface and getQuadSurface
				}

				xmlSettings->popTag(); // surface
			}
		}

		xmlSettings->popTag(); // surfaces
	}
	
	return true;
}

bool SettingsLoader::save(SurfaceStack & surfaces, string fileName){
	
	ofxXmlSettings * xmlSettings = new ofxXmlSettings();

	// Save surfaces
	xmlSettings->addTag("surfaces");
	xmlSettings->pushTag("surfaces");
	for(int i = 0; i < surfaces.size(); i++){
		xmlSettings->addTag("surface");
		xmlSettings->pushTag("surface", i);
		BaseSurface * surface = surfaces[i];

		xmlSettings->addTag("vertices");
		xmlSettings->pushTag("vertices");
		vector <ofVec3f> * vertices = &surface->getVertices();
		for(int j = 0; j < vertices->size(); j++){
			xmlSettings->addTag("vertex");
			xmlSettings->pushTag("vertex", j);
			ofVec3f * vertex = &(*vertices)[j];
			xmlSettings->addValue("x", vertex->x);
			xmlSettings->addValue("y", vertex->y);

			// we don't need z as it will be 0 anyways

			xmlSettings->popTag(); // vertex
		}
		xmlSettings->popTag(); // vertices

		xmlSettings->addTag("texCoords");
		xmlSettings->pushTag("texCoords");
		vector <ofVec2f> * texCoords = &surface->getTexCoords();
		for(int j = 0; j < texCoords->size(); j++){
			xmlSettings->addTag("texCoord");
			xmlSettings->pushTag("texCoord", j);
			ofVec2f * texCoord = &(*texCoords)[j];
			xmlSettings->addValue("x", texCoord->x);
			xmlSettings->addValue("y", texCoord->y);
			xmlSettings->popTag(); // texCoord
		}
		xmlSettings->popTag(); // texCoords
		xmlSettings->addTag("source");
		xmlSettings->pushTag("source");
		
		string sourceTypeName = SourceType::GetSourceTypeName(surface->getSource()->getType());
		
		xmlSettings->addValue("source-type", sourceTypeName);
		xmlSettings->addValue("source-name", surface->getSource()->getName());
		xmlSettings->popTag(); // source
		
		// Save surface options
		// For now only if quad surface
		if(surface->getType() == SurfaceType::QUAD_SURFACE){
			QuadSurface * qs = (QuadSurface *)surface;
			if(!xmlSettings->tagExists("properties")){
				xmlSettings->addTag("properties");
			}
			xmlSettings->pushTag("properties");
			xmlSettings->addValue("perspectiveWarping", qs->getPerspectiveWarping());
			xmlSettings->popTag(); // properties
		}
		
		xmlSettings->popTag(); // surface
	}
	xmlSettings->popTag(); // surfaces
	xmlSettings->save(fileName);
}

BaseSurface * SettingsLoader::getTriangleSurface(ofxXmlSettings * xmlSettings){
	vector <ofVec2f> vertices;
	
	if(xmlSettings->tagExists("vertex", 0)){
		xmlSettings->pushTag("vertex", 0);
		vertices.push_back(ofVec2f(xmlSettings->getValue("x", 0.0f),
								   xmlSettings->getValue("y", 0.0f)));
		xmlSettings->popTag();
	}
	
	if(xmlSettings->tagExists("vertex", 1)){
		xmlSettings->pushTag("vertex", 1);
		vertices.push_back(ofVec2f(xmlSettings->getValue("x", 100.0f),
								   xmlSettings->getValue("y", 0.0f)));
		xmlSettings->popTag();
	}

	if(xmlSettings->tagExists("vertex", 2)){
		xmlSettings->pushTag("vertex", 2);
		vertices.push_back(ofVec2f(xmlSettings->getValue("x", 0.0f),
								   xmlSettings->getValue("y", 100.0f)));
		xmlSettings->popTag();
	}

	xmlSettings->popTag(); // vertices

	vector <ofVec2f> texCoords;

	if(xmlSettings->tagExists("texCoords")){
		xmlSettings->pushTag("texCoords");
		
		if(xmlSettings->tagExists("texCoord", 0)){
			xmlSettings->pushTag("texCoord", 0);
			texCoords.push_back(ofVec2f(xmlSettings->getValue("x", 0.0f),
										xmlSettings->getValue("y", 0.0f)));
			xmlSettings->popTag();
		}
		
		if(xmlSettings->tagExists("texCoord", 1)){
			xmlSettings->pushTag("texCoord", 1);
			texCoords.push_back(ofVec2f(xmlSettings->getValue("x", 1.0f),
										xmlSettings->getValue("y", 0.0f)));
			xmlSettings->popTag();
		}

		if(xmlSettings->tagExists("texCoord", 2)){
			xmlSettings->pushTag("texCoord", 2);
			texCoords.push_back(ofVec2f(xmlSettings->getValue("x", 0.0f),
										xmlSettings->getValue("y", 1.0f)));
			xmlSettings->popTag();
		}

		xmlSettings->popTag(); // texCoords
	}

	// Create and add a triangle surface
	BaseSurface * triangleSurface =
		SurfaceFactory::instance()->createSurface(
			SurfaceType::TRIANGLE_SURFACE);
	triangleSurface->setVertices(vertices);
	triangleSurface->setTexCoords(texCoords);
	
	return triangleSurface;
}

BaseSurface * SettingsLoader::getQuadSurface(ofxXmlSettings * xmlSettings){
	vector <ofVec2f> vertices;
	
	xmlSettings->pushTag("vertex", 0);
	vertices.push_back(ofVec2f(xmlSettings->getValue("x", 0.0f),
							   xmlSettings->getValue("y", 0.0f)));
	xmlSettings->popTag();

	xmlSettings->pushTag("vertex", 1);
	vertices.push_back(ofVec2f(xmlSettings->getValue("x", 100.0f),
							   xmlSettings->getValue("y", 0.0f)));
	xmlSettings->popTag();

	xmlSettings->pushTag("vertex", 2);
	vertices.push_back(ofVec2f(xmlSettings->getValue("x", 100.0f),
							   xmlSettings->getValue("y", 100.0f)));
	xmlSettings->popTag();

	xmlSettings->pushTag("vertex", 3);
	vertices.push_back(ofVec2f(xmlSettings->getValue("x", 0.0f),
							   xmlSettings->getValue("y", 100.0f)));
	xmlSettings->popTag();

	xmlSettings->popTag(); // vertices

	xmlSettings->pushTag("texCoords");

	vector <ofVec2f> texCoords;

	xmlSettings->pushTag("texCoord", 0);
	texCoords.push_back(ofVec2f(xmlSettings->getValue("x", 0.0f),
								xmlSettings->getValue("y", 0.0f)));
	xmlSettings->popTag();

	xmlSettings->pushTag("texCoord", 1);
	texCoords.push_back(ofVec2f(xmlSettings->getValue("x", 1.0f),
								xmlSettings->getValue("y", 0.0f)));
	xmlSettings->popTag();

	xmlSettings->pushTag("texCoord", 2);
	texCoords.push_back(ofVec2f(xmlSettings->getValue("x", 1.0f),
								xmlSettings->getValue("y", 1.0f)));
	xmlSettings->popTag();

	xmlSettings->pushTag("texCoord", 3);
	texCoords.push_back(ofVec2f(xmlSettings->getValue("x", 0.0f),
								xmlSettings->getValue("y", 1.0f)));
	xmlSettings->popTag();

	xmlSettings->popTag(); // texCoords
	
	// Create and add quad surface
	BaseSurface * quadSurface =
		SurfaceFactory::instance()->createSurface(
			SurfaceType::QUAD_SURFACE);
	quadSurface->setVertices(vertices);
	quadSurface->setTexCoords(texCoords);
	
	// Read properties
	// Only perspective warping for now
	bool perspectiveWarping = false;
	if(xmlSettings->tagExists("properties")){
		xmlSettings->pushTag("properties");
		perspectiveWarping = xmlSettings->getValue("perspectiveWarping", false);
		xmlSettings->popTag(); // properties
	}
	QuadSurface * qs = (QuadSurface *)quadSurface;
	qs->setPerspectiveWarping(perspectiveWarping);
	
	return quadSurface;
}

} // namespace piMapper
} // namespace ofx