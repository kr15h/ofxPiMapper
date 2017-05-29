#include "PresentationMode.h"

namespace ofx {
namespace piMapper {

PresentationMode * PresentationMode::_instance = 0;

PresentationMode * PresentationMode::instance(){
	if(_instance == 0){
		_instance = new ofx::piMapper::PresentationMode();
	}
	return _instance;
}

void PresentationMode::draw(Application * app){
	ofPushStyle();
	ofSetColor(255, 255, 255, 255);
	
	app->getSurfaceManager()->draw();
	
	if (_hintCounter > 0)
	{	
		Gui::instance()->getSurfaceHighlightWidget().drawSurfaceOutlines(
			app->getSurfaceManager()->getSelectedSurface());

		_hintCounter--;
	}	
	
	ofPopStyle();

	
}

void PresentationMode::onMousePressed(Application * app, ofMouseEventArgs & args){
    app->getCmdManager()->exec(
        new ofx::piMapper::SetApplicationModeCmd(
            app, ProjectionMappingMode::instance()));
}

void PresentationMode::onKeyPressed(Application * app, ofKeyEventArgs & args)
{
	switch(args.key)
	{
		case ',':
		{
			app->getSurfaceManager()->selectPrevSurface();
			_hintCounter = 30;
			break;
		}
		 
		case '.':
		{
			app->getSurfaceManager()->selectNextSurface();
			_hintCounter = 30;
			break;
		}
		case '!':
		{	
			auto* mediaServer = app->getMediaServer();
			_image_idx = decIndex(_image_idx, mediaServer->getNumImages());
			auto imagePath = mediaServer->getImagePaths().at(_image_idx);
			auto sourceWidget = Gui::instance()->getSourcesEditorWidget();

			app->getCmdManager()->exec(new SetSourceCmd(SourceType::SOURCE_TYPE_IMAGE,
									   imagePath,
									   app->getSurfaceManager()->getSelectedSurface(),
									   &sourceWidget));
			break;
		}
		case '@':
		{
			auto* mediaServer = app->getMediaServer();
			_image_idx = incIndex(_image_idx, mediaServer->getNumImages());
			auto imagePath = mediaServer->getImagePaths().at(_image_idx);
			auto sourceWidget = Gui::instance()->getSourcesEditorWidget();

			app->getCmdManager()->exec(new SetSourceCmd(SourceType::SOURCE_TYPE_IMAGE,
									   imagePath,
									   app->getSurfaceManager()->getSelectedSurface(),
									   &sourceWidget));
			break;
		}
		case '#':
		{	
			auto* mediaServer = app->getMediaServer();
			_video_idx = decIndex(_video_idx, mediaServer->getNumVideos());
			auto videoPath = mediaServer->getVideoPaths().at(_video_idx);
			auto sourceWidget = Gui::instance()->getSourcesEditorWidget();

			app->getCmdManager()->exec(new SetSourceCmd(SourceType::SOURCE_TYPE_VIDEO,
									   videoPath,
									   app->getSurfaceManager()->getSelectedSurface(),
									   &sourceWidget));
			break;
		}
		case '$':
		{
			auto* mediaServer = app->getMediaServer();
			_video_idx = incIndex(_video_idx, mediaServer->getNumVideos());
			auto videoPath = mediaServer->getVideoPaths().at(_video_idx);
			auto sourceWidget = Gui::instance()->getSourcesEditorWidget();

			app->getCmdManager()->exec(new SetSourceCmd(SourceType::SOURCE_TYPE_VIDEO,
									   videoPath,
									   app->getSurfaceManager()->getSelectedSurface(),
									   &sourceWidget));
			break;
		}
		default:
			break;
	}
}

size_t PresentationMode::incIndex(const size_t current, const size_t limit)
{
	size_t next = current + 1;

	if (next >= limit)
		return 0;
	
	return next;

}

size_t PresentationMode::decIndex(const size_t current, const size_t limit)
{
	size_t prev = current - 1;
	
	if (prev == std::numeric_limits<size_t>::max())
		return limit - 1;
	
	return prev;
}

} // namespace piMapper
} // namespace ofx