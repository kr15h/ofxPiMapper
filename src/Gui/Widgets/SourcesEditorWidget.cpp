#include "SourcesEditorWidget.h"

namespace ofx {
namespace piMapper {

SourcesEditorWidget::SourcesEditorWidget(){
	mediaServer = 0;
}

void SourcesEditorWidget::setup(){
	createSelectors();
}

void SourcesEditorWidget::createSelectors(){
	imageSelector = new RadioList();
	videoSelector = new RadioList();
	fboSelector = new RadioList();

	int numImages = mediaServer->getNumImages();
	int numVideos = mediaServer->getNumVideos();
	int numFbos = mediaServer->getNumFboSources();

	// Depending on media count, decide what to load and initialize
	if(numImages){
		// Get image names from media server
		vector <string> imageNames = mediaServer->getImageNames();
		imageSelector->setup("Images", imageNames, mediaServer->getImagePaths());
		ofAddListener(imageSelector->onRadioSelected, this, &SourcesEditorWidget::handleImageSelected);
	}
	if(numVideos){
		vector <string> videoNames = mediaServer->getVideoNames();
		videoSelector->setup("Videos", videoNames, mediaServer->getVideoPaths());
		ofAddListener(videoSelector->onRadioSelected, this, &SourcesEditorWidget::handleVideoSelected);
	}
	if(numFbos){
		vector <string> fboNames = mediaServer->getFboSourceNames();
		fboSelector->setup("FBOs", fboNames, fboNames);
		ofAddListener(fboSelector->onRadioSelected, this, &SourcesEditorWidget::handleFboSelected);
	}

	// Align menus
	int menuPosX = 20;
	int distX = 230;
	if(numImages){
		imageSelector->setPosition(menuPosX, 20);
		menuPosX += distX;
	}
	if(numVideos){
		videoSelector->setPosition(menuPosX, 20);
		menuPosX += distX;
	}
	if(numFbos){
		fboSelector->setPosition(menuPosX, 20);
	}
}

void SourcesEditorWidget::draw(){
	// Don't draw if there is no source selected
	if(surfaceManager->getSelectedSurface() == 0){
		return;
	}
	if(imageSelector->size()){
		imageSelector->draw();
	}
	if(videoSelector->size()){
		videoSelector->draw();
	}
	if(fboSelector->size()){
		fboSelector->draw();
	}
}

// TODO: Redesign the selectors completely so they do not need enable and disable.
void SourcesEditorWidget::disable(){
	if(imageSelector->size()){
		imageSelector->disable();
	}
	if(videoSelector->size()){
		videoSelector->disable();
	}
	if(fboSelector->size()){
		fboSelector->disable();
	}
}

void SourcesEditorWidget::enable(){
	// Don't enable if there is no surface selected
	if(surfaceManager->getSelectedSurface() == 0){
		ofLogNotice("SourcesEditorWidget") << "No surface selected. Not enabling and not showing source list.";
		return;
	}
	if(imageSelector->size()){
		imageSelector->enable();
	}
	if(videoSelector->size()){
		videoSelector->enable();
	}
	if(fboSelector->size()){
		fboSelector->enable();
	}
	BaseSource * source = surfaceManager->getSelectedSurface()->getSource();

	// TODO: getPath should be replaced with something like getId() as now we
	//       use paths for loadable sources and names for FBOs
	if(source->getType() == SourceType::SOURCE_TYPE_FBO){
		selectSourceRadioButton(source->getName());
	}else{
		selectSourceRadioButton(source->getPath());
	}
}

void SourcesEditorWidget::setSurfaceManager(SurfaceManager * newSurfaceManager){
	surfaceManager = newSurfaceManager;
}

void SourcesEditorWidget::setCmdManager(CmdManager * cmdManager){
	_cmdManager = cmdManager;
}

void SourcesEditorWidget::setMediaServer(MediaServer * newMediaServer){
	if(newMediaServer == 0){
		ofLogFatalError("SourcesEditorWidget") << "New media server is 0";
		exit(EXIT_FAILURE);
	}
	
	if(mediaServer != 0){
		removeMediaServerListeners();
	}
	clearMediaServer();
	mediaServer = newMediaServer;
	addMediaServerListeners();
}

MediaServer * SourcesEditorWidget::getMediaServer(){
	return mediaServer;
}

void SourcesEditorWidget::selectSourceRadioButton(string & sourcePath){
	if(sourcePath == ""){
		ofLogNotice("SourcesEditorWidget") << "Path is empty";
		if(imageSelector->size()){
			imageSelector->unselectAll();
		}
		if(videoSelector->size()){
			videoSelector->unselectAll();
		}
		if(fboSelector->size()){
			fboSelector->unselectAll();
		}
		return;
	}else{
		// Check image selector first
		bool imageRadioSelected = false;
		bool videoRadioSelected = false;
		bool fboRadioSelected = false;
		if(imageSelector->size()){
			imageRadioSelected = imageSelector->selectItemByValue(sourcePath);
		}
		if(videoSelector->size()){
			videoRadioSelected = videoSelector->selectItemByValue(sourcePath);
		}
		if(fboSelector->size()){
			fboRadioSelected = fboSelector->selectItemByValue(sourcePath);
		}
		if(imageRadioSelected || videoRadioSelected || fboRadioSelected){
			return;
		}
		// Log warning if we are still here
		ofLogWarning("SourcesEditorWidget") << "Could not find option in any of the source lists";
	}
}

void SourcesEditorWidget::addMediaServerListeners(){
	// Check if the media server is valid
	if(mediaServer == 0){
		ofLogError("SourcesEditorWidget::addMediaServerListeners", "Media server not set");
		return;
	}
	// Add listeners to custom events of the media server
	ofAddListener(mediaServer->onImageAdded, this, &SourcesEditorWidget::handleImageAdded);
	ofAddListener(mediaServer->onImageRemoved, this, &SourcesEditorWidget::handleImageRemoved);
	ofAddListener(mediaServer->onVideoAdded, this, &SourcesEditorWidget::handleVideoAdded);
	ofAddListener(mediaServer->onVideoRemoved, this, &SourcesEditorWidget::handleVideoRemoved);
	ofAddListener(mediaServer->onImageLoaded, this, &SourcesEditorWidget::handleImageLoaded);
	ofAddListener(mediaServer->onImageUnloaded, this, &SourcesEditorWidget::handleImageUnloaded);

	ofAddListener(mediaServer->onFboSourceAdded, this, &SourcesEditorWidget::handleFboSourceAdded);
	ofAddListener(mediaServer->onFboSourceRemoved, this, &SourcesEditorWidget::handleFboSourceRemoved);
	ofAddListener(mediaServer->onFboSourceLoaded, this, &SourcesEditorWidget::handleFboSourceLoaded);
	ofAddListener(mediaServer->onFboSourceUnloaded, this, &SourcesEditorWidget::handleFboSourceUnloaded);

}

void SourcesEditorWidget::removeMediaServerListeners(){
	// Check if the media server is valid
	if(mediaServer == 0){
		ofLogError("SourcesEditorWidget::addMediaServerListeners", "Media server not set");
		return;
	}
	// Remove listeners to custom events of the media server
	ofRemoveListener(mediaServer->onImageAdded, this, &SourcesEditorWidget::handleImageAdded);
	ofRemoveListener(mediaServer->onImageRemoved, this, &SourcesEditorWidget::handleImageRemoved);
	ofRemoveListener(mediaServer->onVideoAdded, this, &SourcesEditorWidget::handleVideoAdded);
	ofRemoveListener(mediaServer->onVideoRemoved, this, &SourcesEditorWidget::handleVideoRemoved);
	ofRemoveListener(mediaServer->onImageLoaded, this, &SourcesEditorWidget::handleImageLoaded);
	ofRemoveListener(mediaServer->onImageUnloaded, this, &SourcesEditorWidget::handleImageUnloaded);
	ofRemoveListener(mediaServer->onFboSourceAdded, this, &SourcesEditorWidget::handleFboSourceAdded);
	ofRemoveListener(mediaServer->onFboSourceRemoved, this, &SourcesEditorWidget::handleFboSourceRemoved);
	ofRemoveListener(mediaServer->onFboSourceLoaded, this, &SourcesEditorWidget::handleFboSourceLoaded);
	ofRemoveListener(mediaServer->onFboSourceUnloaded, this, &SourcesEditorWidget::handleFboSourceUnloaded);
}

void SourcesEditorWidget::handleImageSelected(string & imagePath){
	_cmdManager->exec(new SetSourceCmd(SourceType::SOURCE_TYPE_IMAGE,
									   imagePath,
									   surfaceManager->getSelectedSurface(),
									   (SourcesEditorWidget *)this));
}

void SourcesEditorWidget::setImageSource(string & imagePath){
	// Unselect selected items
	videoSelector->unselectAll();
	fboSelector->unselectAll();

	BaseSurface * surface = surfaceManager->getSelectedSurface();
	if(surface == 0){
		ofLogWarning("SourcesEditorWidget") << "No surface selected";
		return;
	}

	// Unload old media
	BaseSource * source = surface->getSource();
	if(source->isLoadable()){
		mediaServer->unloadMedia(source->getPath());
	}else{
		mediaServer->unloadMedia(source->getName());
	}

	// Load new image
	surface->setSource(mediaServer->loadImage(imagePath));
}

void SourcesEditorWidget::handleVideoSelected(string & videoPath){
	_cmdManager->exec(new SetSourceCmd(SourceType::SOURCE_TYPE_VIDEO,
									   videoPath,
									   surfaceManager->getSelectedSurface(),
									   (SourcesEditorWidget *)this));
}

void SourcesEditorWidget::setVideoSource(string & videoPath){
	// Unselect any selected items
	fboSelector->unselectAll();
	imageSelector->unselectAll();

	BaseSurface * surface = surfaceManager->getSelectedSurface();
	if(surface == 0){
		ofLogWarning("SourcesEditorWidget") << "No surface selected";
		return;
	}

	// Unload old media
	BaseSource * source = surface->getSource();
	if(source->isLoadable()){
		mediaServer->unloadMedia(source->getPath());
	}else{
		mediaServer->unloadMedia(source->getName());
	}

	// Load new video
	surface->setSource(mediaServer->loadVideo(videoPath));
}

void SourcesEditorWidget::handleFboSelected(string & fboName){
	_cmdManager->exec(new SetSourceCmd(SourceType::SOURCE_TYPE_FBO,
									   fboName,
									   surfaceManager->getSelectedSurface(),
									   (SourcesEditorWidget *)this));
}

void SourcesEditorWidget::setFboSource(string & fboName){
	videoSelector->unselectAll();
	imageSelector->unselectAll();

	// Get selected surface
	BaseSurface * surface = surfaceManager->getSelectedSurface();
	if(surface == 0){
		ofLogWarning("SourcesEditorWidget") << "No surface selected";
		return;
	}

	// Unload old media
	BaseSource * source = surface->getSource();
	if(source->isLoadable()){
		mediaServer->unloadMedia(source->getPath());
	}else{
		mediaServer->unloadMedia(source->getName());
	}

	// Load new FBO
	surface->setSource(mediaServer->loadFboSource(fboName));
}

void SourcesEditorWidget::clearSource(){
	BaseSurface * surface = surfaceManager->getSelectedSurface();

	// Unload old media
	BaseSource * source = surface->getSource();
	if(source->isLoadable()){
		mediaServer->unloadMedia(source->getPath());
	}else{
		mediaServer->unloadMedia(source->getName());
	}

	// Reset default source
	surface->setSource(surface->getDefaultSource());
}

void SourcesEditorWidget::clearMediaServer(){
	if(mediaServer == 0){
		return;
	}
	mediaServer->clear();
	delete mediaServer;
	mediaServer = 0;
}

// TODO: There is no need for those at the moment. They add too much overhead.
void SourcesEditorWidget::handleImageAdded(string & path){
	ofLogNotice("SourcesEditorWidget::handleImageAdded")
		<< "Image path: "
		<< path;
}

void SourcesEditorWidget::handleImageRemoved(string & path){}
void SourcesEditorWidget::handleVideoAdded(string & path){}
void SourcesEditorWidget::handleVideoRemoved(string & path){}
void SourcesEditorWidget::handleImageLoaded(string & path){}
void SourcesEditorWidget::handleImageUnloaded(string & path){}
void SourcesEditorWidget::handleFboSourceAdded(string & name){}
void SourcesEditorWidget::handleFboSourceRemoved(string & name){}
void SourcesEditorWidget::handleFboSourceLoaded(string & name){}
void SourcesEditorWidget::handleFboSourceUnloaded(string & name){}

} // namespace piMapper
} // namespace ofx