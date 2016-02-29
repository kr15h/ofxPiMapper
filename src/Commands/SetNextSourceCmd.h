#pragma once

#include "BaseCmd.h"
#include "BaseSurface.h"
#include "SourcesEditor.h"
#include "MediaServer.h"

namespace ofx {
namespace piMapper {

struct SourceData {
	int type;
	string id;
};

class SourcesEditor;

class SetNextSourceCmd : public BaseUndoCmd {

	public:
		SetNextSourceCmd(BaseSurface * surface, SourcesEditor * sourcesEditor);
		void exec();
		void undo();

	private:
		BaseSurface * _surface;
		SourcesEditor * _sourcesEditor;
		vector <SourceData> _sources;
		int _sourceIndex; // Previous source index
		int _nextSourceIndex;

};

} // namespace piMapper
} // namespace ofx

