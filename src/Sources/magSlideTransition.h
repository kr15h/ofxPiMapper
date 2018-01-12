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
	/**
	 * Subclassing notes: Make sure to provide a value for name in your
	 * magSlideTransition subclass.
	 */
	magSlideTransition() { name = "Void"; }
	/**
	 * Begins the transition. This needs to be called in order for the
	 * transition to do anything.
	 * @param nextSlide The subsequent slide in the slide show needs to be
	 * passed here.
	 *
	 * You can override this call to set any initial conditions to the transition,
	 * but make sure to call this method in your override.
	 */
	virtual void start(std::shared_ptr<magSlide> nextSlide);

	/**
	 * Called automatically when the transition is complete. Useful to set
	 * end states for the parameters of the slide and nextSlide. Default implementation
	 * does nothing.
	 */
	virtual void end(){}

	/**
	 * NOTE: The transition settings system is not yet implemented.
	 * Called when the transition is created. Loads settings for magSlideTransition
	 * subclasses. The default implementation does nothing.
	 * @param settings ofParameterGroup with settings for your custom magSlideTransition
	 * subclass.
	 */
	virtual void loadSettings(ofParameterGroup &settings){}

	/**
	 * Updates the transition.
	 * @param timeDelta The elapsed time (in ms.) between the last call to update() and
	 * this one (i.e. the frame time).
	 *
	 * If you need to override update, make sure to call this implementation
	 * in your subclass.
	 */
	virtual void update(u_int64_t timeDelta);

	/**
	 * Draws the transition. Default implementation does nothing.
	 */
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

	std::string const &getName() const
	{
		return name;
	}

	const shared_ptr<magSlide> &getNextSlide() const
	{
		return nextSlide;
	}

	bool isActive() const
	{
		return active;
	}

	/**
	 * Sender is a raw pointer to this magSlideTransition
	 */
	ofEvent<ofEventArgs> transitionCompleteEvent;

protected:
	std::string name;
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
