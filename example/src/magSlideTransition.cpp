//
// magSlideTransition.cpp
// Copyright (c) 2017 Cristobal Mendoza
// http://cuppetellimendoza.com
//

#include "magSlideTransition.h"

std::shared_ptr<magSlideTransition>
magSlideTransition::createTransition(std::string transitionName, std::shared_ptr<magSlide> slide,
								  ofParameterGroup &settings, u_int64_t duration)
{
	auto transition = magSlideTransition::instantiateTransition(transitionName);
	transition->slide = slide;
	transition->duration = duration;
	transition->loadSettings(settings);
	return transition;
}

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

std::shared_ptr<magSlideTransition> magSlideTransition::instantiateTransition(string transitionName)
{
	return std::make_shared<magVoidTransition>();
}

//magDissolveTransition::magDissolveTransition()
//{}
void magVoidTransition::loadSettings(ofParameterGroup &settings)
{
	ofLogNotice("magVoidTransition") << "Void Transition is loading nothing";
}
