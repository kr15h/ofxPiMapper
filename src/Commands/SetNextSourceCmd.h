#pragma once

#include "BaseCmd.h"
#include "BaseSurface.h"
#include "SourcesEditorWidget.h"
#include "MediaServer.h"
#include "Gui.h"

namespace ofx {
namespace piMapper {

struct SourceData {
	int type;
	std::string id;
};

class SourcesEditorWidget;

class SetNextSourceCmd : public BaseUndoCmd {

	public:
		SetNextSourceCmd(BaseSurface * surface, SourcesEditorWidget * sourcesEditor);
		void exec();
		void undo();

	private:
		BaseSurface * _surface;
		SourcesEditorWidget * _sourcesEditor;
		std::vector<SourceData> _sources;
		int _sourceIndex; // Previous source index
		int _nextSourceIndex;

};

} // namespace piMapper
} // namespace ofx

