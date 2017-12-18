#include "MediaServer.h"

namespace ofx {
namespace piMapper {

MediaServer::MediaServer():
	piVideoWatcher(PI_IMAGES_DIR, SourceType::SOURCE_TYPE_VIDEO),
	usb0VideoWatcher(USB0_VIDEOS_DIR, SourceType::SOURCE_TYPE_VIDEO),
	usb1VideoWatcher(USB1_VIDEOS_DIR, SourceType::SOURCE_TYPE_VIDEO),
	usb2VideoWatcher(USB2_VIDEOS_DIR, SourceType::SOURCE_TYPE_VIDEO),
	usb3VideoWatcher(USB3_VIDEOS_DIR, SourceType::SOURCE_TYPE_VIDEO),
    piImageWatcher(PI_IMAGES_DIR, SourceType::SOURCE_TYPE_IMAGE),
	usb0ImageWatcher(USB0_IMAGES_DIR, SourceType::SOURCE_TYPE_IMAGE),
	usb1ImageWatcher(USB1_IMAGES_DIR, SourceType::SOURCE_TYPE_IMAGE),
	usb2ImageWatcher(USB2_IMAGES_DIR, SourceType::SOURCE_TYPE_IMAGE),
	usb3ImageWatcher(USB3_IMAGES_DIR, SourceType::SOURCE_TYPE_IMAGE),
	imageWatcher(ofToDataPath(DEFAULT_IMAGES_DIR, true), SourceType::SOURCE_TYPE_IMAGE),
	videoWatcher(ofToDataPath(DEFAULT_VIDEOS_DIR, true), SourceType::SOURCE_TYPE_VIDEO)
{
	// By initialising all above we also copy files from external media
	// to the ofxPiMapper storage.
	
	imageWatcher = DirectoryWatcher(
		ofToDataPath(DEFAULT_IMAGES_DIR, true),
		SourceType::SOURCE_TYPE_IMAGE);
	
	videoWatcher = DirectoryWatcher(
		ofToDataPath(DEFAULT_VIDEOS_DIR, true),
		SourceType::SOURCE_TYPE_VIDEO);
}

void MediaServer::setup(){
	// We could setup sources here, but the sources are
	// set up while adding them to media server. For now
	// This method is here just to keep things consistent.
}

void MediaServer::update(){
	for(int i = 0; i < fboSources.size(); ++i){
		fboSources[i]->updateFbo();
	}
}

void MediaServer::draw(){
	for(int i = 0; i < fboSources.size(); ++i){
		fboSources[i]->drawFbo();
	}
}

int MediaServer::getNumImages(){
	
	return imageWatcher.getFilePaths().size();
}
int MediaServer::getNumVideos(){
	return videoWatcher.getFilePaths().size();
}
int MediaServer::getNumFboSources(){
	return fboSources.size();
}

vector <string> & MediaServer::getImagePaths(){
	return imageWatcher.getFilePaths();
}

vector <string> MediaServer::getImageNames(){
	vector <string> imageNames;
	for(int i = 0; i < getNumImages(); i++){
		// Split image path
		vector <string> pathParts = ofSplitString(getImagePaths()[i], "/");
		// And get only the last piece
		string name = pathParts[pathParts.size() - 1];
		imageNames.push_back(name);
	}
	return imageNames;
}

vector <string> MediaServer::getFboSourceNames(){
	vector <string> fboSourceNames;
	for(int i = 0; i < fboSources.size(); i++){
		fboSourceNames.push_back(fboSources[i]->getName());
	}
	return fboSourceNames;
}

vector <string> & MediaServer::getVideoPaths(){
	return videoWatcher.getFilePaths();
}

vector <string> MediaServer::getVideoNames(){
	vector <string> videoNames;
	for(int i = 0; i < getNumVideos(); i++){
		// Split video path
		vector <string> pathParts = ofSplitString(getVideoPaths()[i], "/");
		// And get only the last piece
		string name = pathParts[pathParts.size() - 1];
		videoNames.push_back(name);
	}
	return videoNames;
}

BaseSource * MediaServer::loadMedia(string & path, int mediaType){
	// Chose load method depending on type
	if(mediaType == SourceType::SOURCE_TYPE_IMAGE){
		return loadImage(path);
	}else if(mediaType == SourceType::SOURCE_TYPE_VIDEO){
		return loadVideo(path);
	}else if(mediaType == SourceType::SOURCE_TYPE_FBO){
		return loadFboSource(path);
	}else{
		stringstream ss;
		ss << "Can not load media of unknown type: " << mediaType;
		ofLogFatalError("MediaServer") << ss.str();
		std::exit(EXIT_FAILURE);
	}
	return 0;
}

BaseSource * MediaServer::loadImage(string & path){
	ImageSource * imageSource = 0;
	// Check if this image is already loaded
	bool isImageLoaded = false;
	if(loadedSources.count(path)){
		imageSource = static_cast <ImageSource *>(loadedSources[path]);
		isImageLoaded = true;
	}
	// If image is loaded
	if(isImageLoaded){
		// Increase reference count of this source
		//referenceCount[path]++;
		imageSource->referenceCount++;
		stringstream refss;
		refss << "Current reference count for " << path << " = " << imageSource->referenceCount;
		ofLogNotice("MediaServer") << refss.str();
		// Notify objects registered to onImageLoaded event
		stringstream ss;
		ss << "Image " << path << " already loaded";
		ofLogNotice("MediaServer") << ss.str();
		ofNotifyEvent(onImageLoaded, path, this);
		return imageSource;
	}
	// Else load fresh
	imageSource = new ImageSource();
	imageSource->loadImage(path);
	loadedSources[path] = imageSource;
	// Set reference count of this image path to 1
	//referenceCount[path] = 1;
	stringstream refss;
	refss << "Initialized reference count of " << path << " to " << imageSource->referenceCount;
	ofLogNotice("MediaServer") << refss.str();
	// Notify objects registered to onImageLoaded event
	ofNotifyEvent(onImageLoaded, path, this);
	return imageSource;
}

void MediaServer::unloadImage(string & path){
	ImageSource * source = static_cast <ImageSource *>(getSourceByPath(path));
	ofLogNotice("MediaServer") << "Unload image, current reference count: " << source->referenceCount;
	source->referenceCount--;
	// Unload only if reference count is less or equal to 0
	ofLogNotice("MediaServer") << "New reference count: " << source->referenceCount;
	if(source->referenceCount > 0){
		ofLogNotice("MediaServer") << "Not unloading image as it is being referenced elsewhere";
		return;
	}
	// Reference count 0 or less, unload image
	stringstream ss;
	ss << "Removing image " << path;
	ofLogNotice("MediaServer") << ss.str();
	// Destroy image source
	if(loadedSources.count(path)){
		ofLogNotice("MediaServer") << "Source count BEFORE image removal: " << loadedSources.size() << endl;
		loadedSources[path]->clear();
		map <string, BaseSource *>::iterator it = loadedSources.find(path);
		delete it->second;
		loadedSources.erase(it);
		ofLogNotice("MediaServer") << "Source count AFTER image removal: " << loadedSources.size() << endl;
		ofNotifyEvent(onImageUnloaded, path, this);
		return;
	}
	// Something wrong here, we should be out of the routine by now
	stringstream failss;
	failss << "Failed to remove image source: " << path;
	ofLogFatalError("MediaServer") << failss.str();
	std::exit(EXIT_FAILURE);
}

BaseSource * MediaServer::loadVideo(string & path){
	VideoSource * videoSource = 0;
	// Check if this video is already loaded
	bool isVideoLoaded = false;
	if(loadedSources.count(path)){
		videoSource = static_cast <VideoSource *>(loadedSources[path]);
		isVideoLoaded = true;
	}
	// If is loaded
	if(isVideoLoaded){
		// Increase reference count of this source
		videoSource->referenceCount++;
		stringstream refss;
		refss << "Current reference count for " << path << " = " << videoSource->referenceCount;
		ofLogNotice("MediaServer") << refss.str();
		// Notify objects registered to onImageLoaded event
		stringstream ss;
		ss << "Video " << path << " already loaded";
		ofLogNotice("MediaServer") << ss.str();
		ofNotifyEvent(onVideoLoaded, path, this);
		return videoSource;
	}
	// Else load fresh
	videoSource = new VideoSource();
	videoSource->loadVideo(path);
	loadedSources[path] = videoSource;
	// Set reference count of this image path to 1
	//referenceCount[path] = 1;
	stringstream refss;
	refss << "Initialized reference count of " << path << " to " << videoSource->referenceCount;
	ofLogNotice("MediaServer") << refss.str();
	ofNotifyEvent(onVideoLoaded, path, this);
	return videoSource;
}

void MediaServer::unloadVideo(string & path){
	VideoSource * videoSource = static_cast <VideoSource *>(getSourceByPath(path));
	// Decrease reference count of the video
	//referenceCount[path]--;
	videoSource->referenceCount--;
	// Unload only if reference count is less or equal to 0
	if(videoSource->referenceCount > 0){
		ofLogNotice("MediaServer") << "Not unloading video as it is being referenced elsewhere";
		return;
	}
	// Reference count 0 or less, let's unload the video
	ofLogNotice("MediaServer") << "Removing video " << path;
	
	// Distroy video source
	if(loadedSources.count(path)){
		ofLogNotice("MediaServer")
			<< "Source count before video removal: "
			<< loadedSources.size() << endl;
		videoSource->clear();
		map <string, BaseSource *>::iterator it = loadedSources.find(path);
		delete it->second;
		loadedSources.erase(it);
		ofLogNotice("MediaServer")
			<< "Source count after video removal: "
			<< loadedSources.size() << endl;
		ofNotifyEvent(onVideoUnloaded, path, this);
		return;
	}
	
	// Something wrong here, we should be out of the routine by now
	stringstream failss;
	failss << "Failed to remove video source: " << path;
	ofLogFatalError("MediaServer") << failss.str();
	std::exit(EXIT_FAILURE);
}

void MediaServer::unloadMedia(string & path){
	if(loadedSources.count(path)){
		BaseSource * mediaSource = getSourceByPath(path);
		if(mediaSource->getType() == SourceType::SOURCE_TYPE_IMAGE){
			unloadImage(path);
		}else if(mediaSource->getType() == SourceType::SOURCE_TYPE_VIDEO){
			unloadVideo(path);
		}else if(mediaSource->getType() == SourceType::SOURCE_TYPE_FBO){
			unloadFboSource(path);
		}else{
			// Oh my god, what to do!? Relax and exit.
			ofLogFatalError("MediaServer") << "Attempt to unload media of unknown type";
			std::exit(EXIT_FAILURE);
		}
	}else{
		ofLogNotice("MediaServer") << "Nothing to unload";
	}
}

// Clear all loaded media
void MediaServer::clear(){
	typedef map <string, BaseSource *>::iterator it_type;
	for(it_type i = loadedSources.begin(); i != loadedSources.end(); i++){
		// Do not delete FBO source pointers as they are (and should be) initialized elsewhere
		if(i->second->getType() != SourceType::SOURCE_TYPE_FBO){
			delete i->second;
		}
	}
	loadedSources.clear();
}

// TODO: getLoadedSourceByPath
BaseSource * MediaServer::getSourceByPath(string & mediaPath){
	if(loadedSources.count(mediaPath)){
		return loadedSources[mediaPath];
	}
	// Source not found, exit with error
	stringstream ss;
	ss << "Could not find source by path: " << mediaPath;
	ofLogFatalError("MediaServer") << ss.str();
	std::exit(EXIT_FAILURE);
}

string MediaServer::getDefaultImageDir(){
	return DEFAULT_IMAGES_DIR;
}

string MediaServer::getDefaultVideoDir(){
	return DEFAULT_VIDEOS_DIR;
}

string MediaServer::getDefaultMediaDir(int sourceType){
	if(sourceType == SourceType::SOURCE_TYPE_IMAGE){
		return getDefaultImageDir();
	}else if(sourceType == SourceType::SOURCE_TYPE_VIDEO){
		return getDefaultVideoDir();
	}else{
		stringstream ss;
		ss << "Could not get default media dir. Unknown source type: " << sourceType;
		ofLogFatalError("MediaServer") << ss.str();
		std::exit(EXIT_FAILURE);
	}
}

void MediaServer::addFboSource(ofx::piMapper::FboSource & fboSource){
	addFboSource(&fboSource);
}

void MediaServer::addFboSource(FboSource * fboSource){
	ofLogNotice("MediaServer") << "Attempting to add FBO source with name " << fboSource->getName();
	
	// FBO source has to be with unique name
	for(int i = 0; i < fboSources.size(); ++i){
		if(fboSources[i]->getName() == fboSource->getName()){
			ofLogWarning("MediaServer") << "Attempt to add FBO source with duplicate name";
			ofExit(EXIT_FAILURE); // Here we definitely need to fail to avoid confusion
			std::exit(EXIT_FAILURE); // In case the openFrameworks function fails
		}
	}
	
	ofLogNotice("MediaServer") << "Source new, adding";
	fboSources.push_back(fboSource);
    
    // It is important to run the setup of the FBO
    // source from outside as we can see here.
    fboSource->setup();
}

BaseSource * MediaServer::loadFboSource(string & fboSourceName){
	ofLogNotice("MediaServer") << "Attempting to load FBO source with name " << fboSourceName;
	// Search for FBO source name in our storage
	FboSource * source = 0;
	for(int i = 0; i < fboSources.size(); i++){
		if(fboSources[i]->getName() == fboSourceName){
			source = fboSources[i];
			break;
		}
	}
	// Panic if not in storage
	if(source == 0){
		ofLogError("MediaServer") << "Attempt to load non existing FBO source: " << fboSourceName;
		ofExit(EXIT_FAILURE);
	}
	// Check if it is loaded/activated
	if(loadedSources.count(fboSourceName)){
		// Is loaded, increase reference count and return existing
		loadedSources[fboSourceName]->referenceCount++;
		ofLogNotice("MediaServer") << "Current " << fboSourceName << "reference count: " << loadedSources[fboSourceName]->referenceCount;
		return loadedSources[fboSourceName];
	}
	// else
	// Not loaded, add to loaded sources and activate
	// source var should be set by now
	//source->addAppListeners();
	source->referenceCount = 1;
	ofLogNotice("MediaServer") << "Current " << fboSourceName << " reference count: " << source->referenceCount;
	loadedSources[fboSourceName] = source;
	return loadedSources[fboSourceName];
}   // loadFboSource

void MediaServer::unloadFboSource(string & fboSourceName){
	ofLogNotice("MediaServer") << "Attempt to unload FBO source " << fboSourceName;
	// Check if loaded at all
	if(!loadedSources.count(fboSourceName)){
		ofLogWarning("MediaServer") << "FBO source not loaded";
		return;
	}
	// TODO: remove static cast, make the sources handle reference counting,
	// enabling and disabling by themselves
	FboSource * source = static_cast <FboSource *>(loadedSources[fboSourceName]);
	// else decrease reference count
	source->referenceCount--;
	ofLogNotice("MediaServer") << "Current " << fboSourceName << "reference count: " << loadedSources[fboSourceName]->referenceCount;
	// If no references left, disable
	if(source->referenceCount <= 0){
		ofLogNotice("MediaServer") << fboSourceName << " reference count <= 0, removing from loaded sources";
		source->referenceCount = 0;
		//source->removeAppListeners();
		map <string, BaseSource *>::iterator it = loadedSources.find(fboSourceName);
		loadedSources.erase(it);
		ofLogNotice("MediaServer") << "Source count after FBO source removal: " << loadedSources.size() << endl;
		ofNotifyEvent(onFboSourceUnloaded, fboSourceName, this);
	}
}   // unloadFboSource

} // namespace piMapper
} // namespace ofx
