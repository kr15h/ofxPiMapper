#include "BaseSource.h"

namespace ofx {
namespace piMapper {

BaseSource::BaseSource(){
	//cout << "BaseSource" << endl;
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

string & BaseSource::getName(){
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

string & BaseSource::getPath(){
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

void BaseSource::setNameFromPath(string & fullPath){
	vector <string> pathParts;
	//cout << "fullPath: " << fullPath << endl;
	pathParts = ofSplitString(fullPath, "/");   // Maybe on win "/" is "\", have to test
	//cout << "lastPathPart: " << pathParts[pathParts.size() - 1] << endl;
	name = pathParts[pathParts.size() - 1];
}

} // namespace piMapper
} // namespace ofx
