#pragma once

#include "ofMain.h"
#include "SourceType.h"

namespace ofx {
namespace piMapper {

// Use this for adding generative sources to your surfaces
class BaseSource {

	public:
		BaseSource();
		BaseSource(ofTexture * newTexture); // Only one clean way of passing the texture
		~BaseSource();
		ofTexture * getTexture();
		string & getName();
		bool isLoadable(); // Maybe the loading features shoud go to a derrived class
		bool isLoaded(); // as BaseSourceLoadable
		int getType();
		string & getPath();
		virtual void clear(){}

		// TODO: add virtual increaseReferenceCount and decreaseReferenceCount methods
		// and make the variable protected
		int referenceCount;

	private:
		void init();

	protected:
		void setNameFromPath(string & fullPath);
		ofTexture * texture;
		string name;
		string path; // This is set only if loadable is true
		bool loadable; // If the source can be loaded from disk like image and video
		bool loaded; // Is the source loaded?
		int type;

};

} // namespace piMapper
} // namespace ofx
