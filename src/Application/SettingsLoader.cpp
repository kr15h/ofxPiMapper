#include "SettingsLoader.h"

namespace ofx {
namespace piMapper {

SettingsLoader * SettingsLoader::_instance = 0;

SettingsLoader * SettingsLoader::instance(){
	if(_instance == 0){
		_instance = new ofx::piMapper::SettingsLoader();
	}
	return _instance;
}

SettingsLoader::SettingsLoader(){
    _lastLoadedFilename = "surfaces.xml";
}

bool SettingsLoader::load(
	SurfaceManager & surfaceManager,
	MediaServer & mediaServer,
	string fileName){
	
	ofxXmlSettings * xmlSettings = new ofxXmlSettings();
	string sourceType = "";
	string sourceName = "";
	
	BaseSource * source = 0;
	
	if(!xmlSettings->loadFile(fileName)){
		ofLogWarning("SettingsLoader::load()") << "Could not load XML settings";
		return false;
	}
	
	if(!xmlSettings->tagExists("surfaces")){
		xmlSettings->addTag("surfaces");
	}
	
	// Count <surfaces> tags.
	unsigned int numPresets = xmlSettings->getNumTags("surfaces");
	cout << "numPresets: " << numPresets << endl;
		
	// Clear previous presets and surfaces first.
	surfaceManager.clearPresets();
		
	// Loop through <surfaces> tags in the XML.
	for(unsigned int i = 0; i < numPresets; ++i){
	
		xmlSettings->pushTag("surfaces", i);
		
		SurfaceStack * surfaces = surfaceManager.createPreset();

		int numSurfaces = xmlSettings->getNumTags("surface");
		for(int i = 0; i < numSurfaces; i++){
			if(xmlSettings->tagExists("surface", i)){
			
				SurfaceType type = SurfaceType::NONE;
				if(xmlSettings->attributeExists("surface", "type")){
					type = static_cast<SurfaceType>(
						xmlSettings->getAttribute("surface", "type", 0, i));
				}
			
				xmlSettings->pushTag("surface", i);

				// attempt to load surface source
				if(xmlSettings->tagExists("source", 0)){
					xmlSettings->pushTag("source");
					sourceType = xmlSettings->getValue("source-type", "");
					sourceName = xmlSettings->getValue("source-name", "");
					
					if(sourceName != "" && sourceName != "none" && sourceType != ""){

						// Load source depending on type
						SourceType typeEnum = SourceTypeHelper::GetSourceTypeHelperEnum(sourceType);
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
				
				int vertexCount = 0;
				
				if(xmlSettings->tagExists("vertices", 0)){
					xmlSettings->pushTag("vertices");
					vertexCount = xmlSettings->getNumTags("vertex");
					xmlSettings->popTag(); // vertices
				}
				
				if(type == SurfaceType::NONE){
					if(vertexCount == 3){
						type = SurfaceType::TRIANGLE_SURFACE;
					}else if(vertexCount == 4){
						type = SurfaceType::QUAD_SURFACE;
					}else if(vertexCount > 4){
						type = SurfaceType::GRID_WARP_SURFACE;
					}
				}
		
				if(type == SurfaceType::TRIANGLE_SURFACE){
					BaseSurface * triangleSurface = getTriangleSurface(xmlSettings);
					if(sourceName != "none" && source != 0){
						triangleSurface->setSource(source);
					}
					surfaces->push_back(triangleSurface);
				}else if(type == SurfaceType::QUAD_SURFACE){
					BaseSurface * quadSurface = getQuadSurface(xmlSettings);
					if(sourceName != "none" && source != 0){
						quadSurface->setSource(source);
					}
					surfaces->push_back(quadSurface);
				}else if(type == SurfaceType::GRID_WARP_SURFACE){
					BaseSurface * gridWarpSurface = getGridWarpSurface(xmlSettings);
					if(sourceName != "none" && source != 0){
						gridWarpSurface->setSource(source);
					}
					surfaces->push_back(gridWarpSurface);
				}else if(type == SurfaceType::HEXAGON_SURFACE){
					BaseSurface * hexagonSurface = getHexagonSurface(xmlSettings);
					if(sourceName != "none" && source != 0){
						hexagonSurface->setSource(source);
					}
					surfaces->push_back(hexagonSurface);
				}

				xmlSettings->popTag(); // surface
			}
		}

		xmlSettings->popTag(); // surfaces
		
	} // for
	
	_lastLoadedFilename = fileName;
	
	return true;
}

// TODO: Save all presets, not just the active one.
bool SettingsLoader::save(SurfaceManager & surfaceManager, string fileName){
	
	ofxXmlSettings * xmlSettings = new ofxXmlSettings();
	
	unsigned int numPresets = surfaceManager.getNumPresets();
	
	for(unsigned int i = 0; i < numPresets; ++i){
	
	SurfaceStack * surfaces = surfaceManager.getPresetAt(i);

	// Save surfaces
	xmlSettings->addTag("surfaces");
	xmlSettings->pushTag("surfaces", i);
	for(int i = 0; i < surfaces->size(); i++){
		BaseSurface * surface = surfaces->at(i);
		
		xmlSettings->addTag("surface");
		xmlSettings->addAttribute("surface", "type", surface->getType(), i);
		xmlSettings->pushTag("surface", i);
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
		
		string sourceTypeName = SourceTypeHelper::GetSourceTypeHelperName(surface->getSource()->getType());
		
		xmlSettings->addValue("source-type", sourceTypeName);
		string sourceName = surface->getSource()->getName();
		xmlSettings->addValue("source-name", (sourceName == "") ? "none" : sourceName);
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
		}else if(surface->getType() == SurfaceType::GRID_WARP_SURFACE){
			GridWarpSurface * gws = (GridWarpSurface *)surface;
			if(!xmlSettings->tagExists("properties")){
				xmlSettings->addTag("properties");
			}
			xmlSettings->pushTag("properties");
			xmlSettings->addValue("gridCols", gws->getGridCols());
			xmlSettings->addValue("gridRows", gws->getGridRows());
			xmlSettings->popTag();
		}
		
		xmlSettings->popTag(); // surface
	}
	xmlSettings->popTag(); // surfaces
	
	} // for
	
	xmlSettings->save(fileName);
}

bool SettingsLoader::create(string fileName){
	ofxXmlSettings xml;
	xml.addTag("surfaces");
	return xml.save(fileName);
}

BaseSurface * SettingsLoader::getTriangleSurface(ofxXmlSettings * xmlSettings){
	vector <ofVec2f> vertices;
	
	if(xmlSettings->tagExists("vertices")){
		xmlSettings->pushTag("vertices");
	
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
	}

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
	
	if(xmlSettings->tagExists("vertices")){
		xmlSettings->pushTag("vertices");
	
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
			vertices.push_back(ofVec2f(xmlSettings->getValue("x", 100.0f),
							           xmlSettings->getValue("y", 100.0f)));
			xmlSettings->popTag();
		}

		if(xmlSettings->tagExists("vertex", 3)){
			xmlSettings->pushTag("vertex", 3);
			vertices.push_back(ofVec2f(xmlSettings->getValue("x", 0.0f),
								       xmlSettings->getValue("y", 100.0f)));
			xmlSettings->popTag();
		}

		xmlSettings->popTag(); // vertices
	}
	
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
			texCoords.push_back(ofVec2f(xmlSettings->getValue("x", 1.0f),
										xmlSettings->getValue("y", 1.0f)));
			xmlSettings->popTag();
		}

		if(xmlSettings->tagExists("texCoord", 3)){
			xmlSettings->pushTag("texCoord", 3);
			texCoords.push_back(ofVec2f(xmlSettings->getValue("x", 0.0f),
										xmlSettings->getValue("y", 1.0f)));
			xmlSettings->popTag();
		}

		xmlSettings->popTag(); // texCoords
	}
	
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

BaseSurface * SettingsLoader::getGridWarpSurface(ofxXmlSettings * xmlSettings){
	vector <ofVec2f> vertices;
	
	if(xmlSettings->tagExists("vertices")){
		xmlSettings->pushTag("vertices");
		
		int iv = 0;
		
		while(xmlSettings->tagExists("vertex", iv)){
			xmlSettings->pushTag("vertex", iv);
			vertices.push_back(ofVec2f(xmlSettings->getValue("x", 0.0f),
								       xmlSettings->getValue("y", 0.0f)));
			xmlSettings->popTag();
			++iv;
		}

		xmlSettings->popTag(); // vertices
	}
	
	vector <ofVec2f> texCoords;

	if(xmlSettings->tagExists("texCoords")){
		xmlSettings->pushTag("texCoords");

		int it = 0;
		
		while(xmlSettings->tagExists("texCoord", it)){
			xmlSettings->pushTag("texCoord", it);
			texCoords.push_back(ofVec2f(xmlSettings->getValue("x", 0.0f),
										xmlSettings->getValue("y", 0.0f)));
			xmlSettings->popTag();
			++it;
		}

		xmlSettings->popTag(); // texCoords
	}
	
	// Read properties
	// Only perspective warping for now
	int gridCols = 0;
	int gridRows = 0;
	if(xmlSettings->tagExists("properties")){
		xmlSettings->pushTag("properties");
		gridCols = xmlSettings->getValue("gridCols", 0);
		gridRows = xmlSettings->getValue("gridRows", 0);
		xmlSettings->popTag(); // properties
	}
	
	// Create and add quad surface
	BaseSurface * gridWarpSurface =
		SurfaceFactory::instance()->createSurface(
			SurfaceType::GRID_WARP_SURFACE);
	((GridWarpSurface *)gridWarpSurface)->setGridCols(gridCols);
	((GridWarpSurface *)gridWarpSurface)->setGridRows(gridRows);
	((GridWarpSurface *)gridWarpSurface)->createGridMesh();
	gridWarpSurface->setVertices(vertices);
	gridWarpSurface->setTexCoords(texCoords);
	
	return gridWarpSurface;
}

BaseSurface * SettingsLoader::getHexagonSurface(ofxXmlSettings * xmlSettings){
	vector <ofVec2f> vertices;
	
	if(xmlSettings->tagExists("vertices")){
		xmlSettings->pushTag("vertices");
		
		unsigned int v = 0;
		while(xmlSettings->tagExists("vertex", v)){
			xmlSettings->pushTag("vertex", v);
			vertices.push_back(ofVec2f(xmlSettings->getValue("x", 0.0f),
									   xmlSettings->getValue("y", 0.0f)));
			xmlSettings->popTag(); // vertex
			v += 1;
		}

		xmlSettings->popTag(); // vertices
	}

	vector <ofVec2f> texCoords;

	if(xmlSettings->tagExists("texCoords")){
		xmlSettings->pushTag("texCoords");
		
		unsigned int t = 0;
		while(xmlSettings->tagExists("texCoord", t)){
			xmlSettings->pushTag("texCoord", t);
			texCoords.push_back(ofVec2f(xmlSettings->getValue("x", 0.0f),
										xmlSettings->getValue("y", 0.0f)));
			xmlSettings->popTag(); // texCoord
			t += 1;
		}

		xmlSettings->popTag(); // texCoords
	}

	// Create and add a triangle surface
	BaseSurface * hexagonSurface =
		SurfaceFactory::instance()->createSurface(
			SurfaceType::HEXAGON_SURFACE);
	hexagonSurface->setVertices(vertices);
	hexagonSurface->setTexCoords(texCoords);
	
	return hexagonSurface;
}

} // namespace piMapper
} // namespace ofx
