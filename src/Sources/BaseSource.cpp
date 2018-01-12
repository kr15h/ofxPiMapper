#include "BaseSource.h"

namespace ofx {
namespace piMapper {

BaseSource::BaseSource(){
	//std::cout << "BaseSource" << std::endl;
	init();
    runInBackground = false;
    displayed = false;
}

BaseSource::BaseSource(ofTexture * newTexture){
	init();
	texture = newTexture;
}

BaseSource::~BaseSource(){}

ofTexture * BaseSource::getTexture(){
	return texture;
}

std::string & BaseSource::getName(){
	return name;
}

bool BaseSource::isLoadable(){
	return loadable;
}

bool BaseSource::isLoaded(){
	return loaded;
}

SourceType BaseSource::getType(){
	return type;
}

std::string & BaseSource::getPath(){
	return path;
}

void BaseSource::init(){
	texture = 0;
	name = "";
	path = "";
	loadable = false;
	loaded = false;
	type = SourceType::SOURCE_TYPE_NONE;
	referenceCount = 1;   // We have one instance on init
}

void BaseSource::setActive(bool value){
    displayed = value;
}

bool BaseSource::isActive(){
    return displayed;
}

bool BaseSource::runsInBackground(){
    return runInBackground;
}

void BaseSource::setNameFromPath(std::string & fullPath){
	std::vector<std::string> pathParts;
	//std::cout << "fullPath: " << fullPath << std::endl;

	pathParts = ofSplitString(fullPath, "/");   // Maybe on win "/" is "\", have to test
	//std::cout << "lastPathPart: " << pathParts[pathParts.size() - 1] << std::endl;
	name = pathParts[pathParts.size() - 1];
}

} // namespace piMapper
} // namespace ofx
