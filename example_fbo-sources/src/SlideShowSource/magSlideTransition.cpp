//
// magSlideTransition.cpp
// Copyright (c) 2017 Cristobal Mendoza
// http://cuppetellimendoza.com
//

#include "magSlideTransition.h"

void magSlideTransition::start(std::shared_ptr<magSlide> nextSlide)
{
	runningTime = 0;
	active =  true;
	this->nextSlide = nextSlide;
}

void magSlideTransition::update(uint64_t timeDelta)
{
	if (!active) return;

	runningTime += timeDelta;
	if (runningTime >= duration)
	{
		ofEventArgs arghh;	// arghhhh...
		nextSlide->setOpacity(255);
		nextSlide->setPosition(0, 0);
		end();
		transitionCompleteEvent.notify(this, arghh);
		active = false;
	}

}

uint64_t magSlideTransition::getRunningTime()
{
	return runningTime;
}

float magSlideTransition::getNormalizedTime()
{
	return (double)runningTime / (double)duration;
}


void magDissolveTransition::draw()
{
	slide->setOpacity(255 - (getNormalizedTime() * 255));
	nextSlide->setOpacity(getNormalizedTime()*255);
}

void magDissolveTransition::start(std::shared_ptr<magSlide> nextSlide)
{
	magSlideTransition::start(nextSlide);
	nextSlide->setOpacity(0);
}

void magDissolveTransition::end()
{
	nextSlide->setOpacity(255);
	slide->setOpacity(0);
}
