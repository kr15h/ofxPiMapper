//
// magSlideTransition.h
// Copyright (c) 2017 Cristobal Mendoza
// http://cuppetellimendoza.com
//

#ifndef MAGSLIDETRANSITION_H
#define MAGSLIDETRANSITION_H


#include "magSlide.h"

class magSlideTransition
{
public:
	static std::shared_ptr<magSlideTransition> createTransition(string transitionName,
																shared_ptr<magSlide> ptr,
																ofParameterGroup &group,
																u_int64_t i);
	/**
	 * Begins the transition. This must be called in order for the
	 * transition to actually do anything!
	 */
	void start();
	virtual void loadSettings(ofParameterGroup &settings) = 0;
	virtual void setup(){}
	virtual void update(u_int64_t timeDelta);
	virtual void draw(){}

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

	ofEvent<ofEventArgs> transitionCompleteEvent;

protected:
	magSlideTransition(){}
	std::shared_ptr<magSlide> slide;
	u_int64_t runningTime;
	u_int64_t duration;
	u_int64_t endTime;
	bool isActive = false;
	static shared_ptr<magSlideTransition> instantiateTransition(string transitionName);
};

class magVoidTransition : public magSlideTransition
{
public:
	void loadSettings(ofParameterGroup &settings) override;
};

class magDissolveTransition : public magSlideTransition
{
public:

};

#endif
