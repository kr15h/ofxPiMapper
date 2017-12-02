//
//  Created by Cristobal Mendoza on 11/9/17.
//

#ifndef MAGSLIDE_H
#define MAGSLIDE_H

#include "ofMain.h"

class magSlideTransition;

class magSlide
{
public:
	magSlide(std::string type);
//    ~magSlide();
	virtual void update(u_int64_t deltaTime);
	virtual void draw() = 0;

	/**
	 * Sets the slide up for playback. This method must be
	 * called before displaying the slide.
	 * @param startTime
	 */
	void start(u_int64_t startTime);

	enum ResizeOptions : short
	{
		/**
		 * No resizing applied, displays the slide in its native pixel dimensions.
		 * This is the default behavior.
		 */
				NoResize = 0,
		/**
		 * Explicitly set a slide to display in its native dimension.
		 * None and NoResize result in the same output, but if you specify
		 * a default resizing option in your slideshow and you want a particular
		 * slide not to resize, you must specify this option. Otherwise the
		 * slide show option will apply.
		 */
				Native,

		/**
		 * Sets width and height to match the source's.
		 * This will distort the slide if the aspect ratios
		 * don't match.
		 */
				Fit,

		/**
		 * Resizes the largest dimension to the source's max,
		 * the other dimension is resized proportionally.
		*/
				FitProportionally,

		/**
		 * Resizes the shortest dimensions to the source's max,
		 */
				FillProportionally,
	};

	enum SlideState : short
	{
		Off = 0,
		BuildIn,
		Normal,
		BuildOut,
		Complete
	};

	const std::string &getType()
	{ return type; }

	float getWidth()
	{ return width; }

	float getHeight()
	{ return height; }

	/**
	 * Change the display size of a slide. This will implicitly
	 * set resizeOptions to ResizeOption.NoResize.
	 * This method does not resize the pixel source of the slide.
	 * @param w The new width
	 * @param h The new height
	 */
	virtual void setSize(float w, float h);

	u_int64_t getDuration()
	{
		return duration;
	}

	/**
	 * Sets the display time of the slide, excluding
	 * builds (in or out)
	 * @param duration in milliseconds.
	 */
	void setDuration(u_int64_t duration);

	/**
	 * Sets the duration of the buildIn and buildOut
	 * transitions. Transition times are added to the
	 * duration of the slide.
	 * @param tDuration in milliseconds.
	 */
	void setTransitionDuration(u_int64_t tDuration);
	ResizeOptions getResizeOption() const;
	void setResizeOption(ResizeOptions resizeOption);

	SlideState getSlideState() const
	{
		return slideState;
	}

	bool isSlideComplete()
	{ return isComplete; }

	int getId()
	{ return id; }

	const std::string getSlideStateName();

	//////////////////////////////
	/// Events
	//////////////////////////////
	ofEvent<ofEventArgs> slideCompleteEvent;
	ofEvent<ofEventArgs> slideStateChangedEvent;

	friend class magSlideShowSource;

protected:
	int id;
	std::string type;
	float width;
	float height;
	ofPoint position;
	ResizeOptions resizeOption = NoResize;
	SlideState slideState = Off;
	bool isComplete = false;

	std::shared_ptr<magSlideTransition> buildIn = nullptr;
	std::shared_ptr<magSlideTransition> buildOut = nullptr;
	std::shared_ptr<magSlideTransition> activeTransition = nullptr;
	/**
	 * The duration of the slide in millis, not counting builds
	 */
	u_int64_t duration;

	/**
	* The start time of the slide in milliseconds, in "local time".
	 * In practice, this means that the start time is always 0.
	*/
	u_int64_t startTime;

	/**
	 * The end time of the slide in milliseconds, in "local time".
	 * The endTime is startTime + buildInDuration + duration + buildOutDuration.
	 */
	u_int64_t endTime;

	/**
	 * The duration of the build in transition or effect, in milliseconds.
	 */
	u_int64_t buildInDuration;

	/**
	 * The duration of the build out transition or effect, in milliseconds.
	 */
	u_int64_t buildOutDuration;

	/**
	 * The "local time" start of the build out transition. This time should also
	 * signal the enqueuing of the next slide, if applicable.
	 */
	u_int64_t buildOutStartTime;

	/**
	 * The amount of time the slide has been displayed, in milliseconds.
	 * This constitutes the "local time" of the slide.
	 */
	u_int64_t runningTime;

	void setState(SlideState state);

	static int idCount;
};

class magImageSlide : public magSlide
{
public:
	magImageSlide();
	~ magImageSlide();
	/**
	 * Sets up an image slide.
	 * @param image is copied into the member magImageSlide::image and is
	 * not modified in any way.
	 */
	void setup(ofImage &image);

	void draw();

protected:
	ofImage image;
};

class magVideoSlide : public magSlide
{
public:
	magVideoSlide();
	~magVideoSlide();
	bool setup(ofFile &file, bool useVideoDuration = false);
	void update();
	void draw();

	/**
	 * Sets the slide duration to the duration of the video.
	 * magSlide::duration will be changed by this call, so if you later
	 * change your mind you'll have to use magSlide::setDuration.
	 */
	void useVideoForDuration();
protected:
	ofVideoPlayer videoPlayer;
};

#endif
