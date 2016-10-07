#pragma once

#include "BaseCmd.h"
#include "Application.h"

namespace ofx {
namespace piMapper {

class Application;
class ApplicationBaseMode;

class SetApplicationModeCmd : public BaseUndoCmd {

	public:
		SetApplicationModeCmd(
			Application * app,
			ApplicationBaseMode * st);

		void exec();
		void undo();

	private:
		Application * _application;
		ApplicationBaseMode * _prevApplicationState;
		ApplicationBaseMode * _applicationState;
	
		ofPoint _translation;

};

} // namespace piMapper
} // namespace ofx

