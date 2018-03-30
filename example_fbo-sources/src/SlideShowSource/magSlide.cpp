//
// magSlide.cpp
// Copyright (c) 2017 Cristobal Mendoza
// http://cuppetellimendoza.com
//

#include "magSlide.h"
#include "magSlideTransition.h"

#pragma mark magSlide

int magSlide::idCount = 0;

magSlide::magSlide(std::string type)
{
    this->type = type;
    position = ofPoint(0, 0);
    id = magSlide::idCount;
    magSlide::idCount++;
}

void magSlide::update(u_int64_t deltaTime)
{
	transition->update(deltaTime);
    runningTime += deltaTime;

    switch (slideState){
//        case SlideState::BuildIn:
//            if (runningTime >= buildInDuration)
//            {
//                setState(Normal);
//				activeTransition = nullptr;
//            }
//            break;

        case SlideState::Normal:
            if (runningTime >= buildOutStartTime){
				setState(BuildOut);
			}
            break;

        case SlideState::BuildOut:
            if (runningTime >= endTime){
                setState(Complete);
            }
            break;
		default:
			break;
    }
}

void magSlide::setSize(float w, float h)
{
    width = w;
    height = h;
}

void magSlide::setResizeOption(magSlide::ResizeOptions resizeOption)
{
    this->resizeOption = resizeOption;
}

magSlide::ResizeOptions magSlide::getResizeOption() const
{
	return resizeOption;
}

void magSlide::setDuration(u_int64_t duration)
{
    this->duration = duration;
}

void magSlide::setState(SlideState state)
{
    // Don't do anything if the new state is the same
    // as the current one:
    if (slideState == state) return;

    slideState = state;
    ofEventArgs args;
    ofNotifyEvent(slideStateChangedEvent, args, this);

    if (slideState == Complete)
    {
        ofNotifyEvent(slideCompleteEvent, args, this);
    }
}

void magSlide::setTransitionDuration(u_int64_t tDuration)
{
    buildOutDuration = tDuration;
}

const std::string magSlide::getSlideStateName()
{
    switch (slideState)
    {
//        case SlideState::BuildIn:
//            return "BuildIn";
        case SlideState::BuildOut:
            return "BuildOut";
        case Normal:
            return "Normal";
        case SlideState::Complete:
            return "Complete";
        case SlideState::Off:
            return "Off";
    }

    return "unknown";
}

void magSlide::start(u_int64_t startTime)
{
	this->startTime = startTime;
	runningTime = 0;
	endTime = duration + (buildOutDuration*2); // *2 because we take into account transition in and out
	buildOutStartTime = duration + buildOutDuration;
	slideState = magSlide::SlideState::Normal;
	position.set(0, 0);
	opacity = 255;
	isComplete = false;
}

void magSlide::draw()
{
	ofSetColor(255, opacity);
	if(transition->isActive())
	{
		transition->draw();
	}
}


////////////////////////////////////////////////////////
#pragma mark MAG_IMAGE_SLIDE
////////////////////////////////////////////////////////

magImageSlide::magImageSlide() : magSlide("magImageSlide") {}

magImageSlide::~magImageSlide() {}

void magImageSlide::setup(ofImage &image)
{
    // Make a copy of the image:
    this->image = ofImage(image);
    image.setAnchorPercent(0.5, 0.5);
	width = image.getWidth();
	height = image.getHeight();
}

void magImageSlide::draw()
{
	magSlide::draw();
    image.draw(position, width, height);
}

////////////////////////////////////////////////////////
#pragma mark MAG_VIDEO_SLIDE
////////////////////////////////////////////////////////

magVideoSlide::magVideoSlide() : magSlide("magVideoSlide")
{}

magVideoSlide::~magVideoSlide()
{
	videoPlayer.stop();
}

bool magVideoSlide::setup(ofFile &file, bool useVideoDuration)
{

    bool success = videoPlayer.load(file.getAbsolutePath());

    if (success)
    {
        videoPlayer.setAnchorPercent(0.5, 0.5);
        if (useVideoDuration)
        {
            useVideoForDuration();
        }
    }

    return success;
}

void magVideoSlide::update()
{
	videoPlayer.update();
}

void magVideoSlide::draw()
{
	magSlide::draw();
	videoPlayer.draw(position.x, position.y, width, height);
}

void magVideoSlide::useVideoForDuration()
{
    duration = u_int64_t((videoPlayer.getDuration()*1000)) - buildOutDuration;
}

