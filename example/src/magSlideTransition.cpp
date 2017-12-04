//
// magSlideTransition.cpp
// Copyright (c) 2017 Cristobal Mendoza
// http://cuppetellimendoza.com
//

#include "magSlideTransition.h"

void magSlideTransition::start()
{
	runningTime = 0;
	isActive =  true;
}

void magSlideTransition::update(u_int64_t timeDelta)
{
	if (!isActive) return;

	runningTime += timeDelta;
	if (runningTime >= duration)
	{
		ofEventArgs arghh;	// arghhhh...
		transitionCompleteEvent.notify(this, arghh);
		isActive = false;
	}

}

u_int64_t magSlideTransition::getRunningTime()
{
	return runningTime;
}

float magSlideTransition::getNormalizedTime()
{
	return (double)runningTime / (double)duration;
}

void magFadeInTransition::draw()
{
	ofLogVerbose() << "fade in draw";
	ofSetColor(255, getNormalizedTime() * 255);
}