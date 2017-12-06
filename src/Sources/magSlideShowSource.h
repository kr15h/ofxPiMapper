//
// magSlideShowSource.h
// Copyright (c) 2017 Cristobal Mendoza
// http://cuppetellimendoza.com
//

#ifndef MAGSLIDESHOWSOURCE_H
#define MAGSLIDESHOWSOURCE_H

#include "FboSource.h"
#include "magSlide.h"
#include "DirectoryWatcher.h"

class magSlide;


class magSlideShowSource : public ofx::piMapper::FboSource {
	public:
		magSlideShowSource();
		struct Settings; // forward declaration
		bool initialize(magSlideShowSource::Settings settings);
		void setup() override;
		void update() override;
		void draw() override;

		/**
		 * Removes all slides and then attempts to create a new slide show
		 * based on the contents of the ofDirectory specified. The files may
		 * be images or videos, which will be transformed into the appropriate slide type.
		 * Any other file type in the directory is ignored (including other directories).
		 * The slide order is alphabetical according to filename.
		 *
		 * @param dir The ofDirectory to use as a source for a slide show.
		 * @return true if at least one slide was created. false is returned
		 * otherwise. Check the console for the specific error.
		 */
		bool createFromFolderContents(std::string path);

		bool loadFromXml();
		void addSlide(std::shared_ptr<magSlide> slide);
		void play();
		void pause();
		void playNextSlide();
		void playPrevSlide();
		void playSlide(int slideIndex);

		enum LoopType : int {
			NONE = 0,
			NORMAL,
			PING_PONG
		};

		struct Settings {
			/**
			 * The pixel width of the FBO.
			 */
			float width = 1280;

			/**
			 * The pixel height of the FBO.
			 */
			float height = 720;
			/**
			 * An optional default slide duration, in seconds.
			 * If a slide specifies a duration this value is ignored.
			 */
			float slideDuration = 5;

			/**
			 * An optional default transition for the slide show.
			 */
			std::string transitionName = "";

			/**
			 * An optional default transition duration. If no transition
			 * is specified, this value is ignored;
			 */
			float transitionDuration = 0;

			/**
			 * If specified, all applicable files in the folder will
			 * be used as slides in the slide show. They will be ordered
			 * alphabetically according to their file names.
			 *
			 * If path is relative, the root will likely be the Data folder.
			 */
			std::string slidesFolderPath = "sources/images";

			/**
			 * If specified,
			 */
			std::string slideshowFilePath;


			/**
			 * Loop type for the slide show. See @code LoopType for options.
			 * The default is @code LoopType:None.
			 */
			LoopType loopType = LoopType::NONE;

			/**
			 * The number of loops to perform, if the loopType is not NONE.
			 * If the value is 0 or less than 0, the slide show loops forever.
			 */
			int numLoops = 0;

			/**
			 * The resizing option for the slide show. The default is FitProportionally.
			 * If a slide already has a resizing option applied, that option will be
			 * respected and this resizeOption will not be used.
			 */
			magSlide::ResizeOptions resizeOption = magSlide::ResizeOptions::FitProportionally;
		};

		////////////////////////////////////////////
		//// Event Listeners
		////////////////////////////////////////////
		void slideStateChanged(const void *sender, ofEventArgs &args);
		void slideComplete(const void *sender, ofEventArgs &args);
		virtual ~magSlideShowSource();


		/**
		 * Fires when the slide show is done, which happens when
		 * the loop count is equal to Settings::numLoops, or when
		 * the last slide is played when @code LoopType::NONE is specified.
		 * Sender is this slide show.
		 */
		ofEvent<ofEventArgs> slideshowCompleteEvent;


		/**
		 * Fires when the slide show reaches the last slide
		 * and will perform a loop in the next call.
		 * Sender is this slide show.
		 */
		ofEvent<ofEventArgs> slideshowWillLoopEvent;

	protected:
		Settings settings;
		std::vector<std::shared_ptr<magSlide>> slides;

	private:
//    std::shared_ptr<magSlide> currentSlide;
		std::vector<std::shared_ptr<magSlide>> activeSlides;
		void enqueueSlide(std::shared_ptr<magSlide> slide, u_int64_t startTime);

		u_int64_t lastTime;
		u_int64_t deltaTime;
		u_int64_t runningTime;

		bool isInitialized = false;
		bool isPlaying = false;
		int currentSlideIndex = 0;
		int direction = 1;
		int loopCount = 0;
		ofx::piMapper::DirectoryWatcher* directoryWatcher;
		void fileAddedListener(const void *sender);
		void fileRemovedListener(const void *sender);
		bool doInit;
};


#endif
