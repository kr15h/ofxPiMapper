// SetSourceCmd
// Set selected surface source undoable command
// Created by Krisjanis Rijnieks 2015-05-20

#pragma once

#include "BaseCmd.h"
#include "BaseSurface.h"
#include "SourcesEditor.h"

namespace ofx {
namespace piMapper {

class SourcesEditor;

class SetSourceCmd : public BaseUndoCmd {

	public:
		SetSourceCmd(int sourceType,
					 string sourceId,
					 BaseSurface * surface,
					 SourcesEditor * sourcesEditor);
		void exec();
		void undo();

	private:
		int _sourceType;
		string _sourceId;
		BaseSurface * _surface;
		SourcesEditor * _sourcesEditor;

		int _oldSourceType;
		string _oldSourceId;

};

} // namespace piMapper
} // namespace ofx

