#pragma once

#include "ofMain.h"

namespace ofx {
namespace piMapper {

class Settings {
	public:
		Settings();
	
		void load();
		void save();
};

}
}