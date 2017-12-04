//
// magSlideTransition.h
// Copyright (c) 2017 Cristobal Mendoza
// http://cuppetellimendoza.com
//

#ifndef MAGSLIDETRANSITION_H
#define MAGSLIDETRANSITION_H

#include "magSlide.h"

class magSlideTransitionFactory;

class magSlideTransition
{
public:
	magSlideTransition() {}
	/**
	 * Begins the transition. This must be called in order for the
	 * transition to actually do anything!
	 */
	void start();
	virtual void loadSettings(ofParameterGroup &settings){}
	virtual void update(u_int64_t timeDelta);
	virtual void draw(){
		ofLogVerbose() << "transiwiton draw " << getNormalizedTime();
	}

	/**
	 * Current running time in milliseconds.
	 * @return u_int64_t
	 */
	u_int64_t getRunningTime();

	/**
	 * Returns the current time in normalized form.
	 * 0 = start, 1 = end.
	 * @return Float between 0 and 1.
	 */
	float getNormalizedTime();

	string const &getName() const
	{
		return name;
	}

	ofEvent<ofEventArgs> transitionCompleteEvent;

protected:
	std::string name = "Void";
	std::shared_ptr<magSlide> slide;
	u_int64_t runningTime;
	u_int64_t duration;
	u_int64_t endTime;
	bool isActive = false;

	friend class magSlideTransitionFactory;
};

class magFadeInTransition : public magSlideTransition
{
public:
	magFadeInTransition()
	{
		name = "FadeIn";
	}

	void draw() override ;
};



#endif
