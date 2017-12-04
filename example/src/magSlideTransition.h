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
	virtual void start(std::shared_ptr<magSlide> nextSlide);
	virtual void end(){}
	virtual void loadSettings(ofParameterGroup &settings){}
	virtual void update(u_int64_t timeDelta);
	virtual void draw(){
		ofLogNotice("magSlideTransition") << "transition draw - this should be overriden " << getNormalizedTime();
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

	const shared_ptr<magSlide> &getNextSlide() const
	{
		return nextSlide;
	}

	void setNextSlide(shared_ptr<magSlide> nextSlide)
	{
		magSlideTransition::nextSlide = nextSlide;
	}

	bool isActive() const
	{
		return active;
	}

	ofEvent<ofEventArgs> transitionCompleteEvent;

protected:
	std::string name = "Void";
	std::shared_ptr<magSlide> slide;
	std::shared_ptr<magSlide> nextSlide;

	u_int64_t runningTime;
	u_int64_t duration;
	u_int64_t endTime;
	bool active = false;


protected:

	friend class magSlideTransitionFactory;
};

class magDissolveTransition : public magSlideTransition
{
public:
	magDissolveTransition()
	{
		name = "Dissolve";
	}

	void start(std::shared_ptr<magSlide> nextSlide) override;

	void draw() override;
	void end() override;
};

#endif
