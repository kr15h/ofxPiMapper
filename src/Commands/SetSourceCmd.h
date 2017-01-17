// SetSourceCmd
// Set selected surface source undoable command
// Created by Krisjanis Rijnieks 2015-05-20

#pragma once

#include "BaseCmd.h"
#include "BaseSurface.h"
#include "SourcesEditorWidget.h"

namespace ofx {
namespace piMapper {

class SourcesEditorWidget;

class SetSourceCmd : public BaseUndoCmd {

	public:
		SetSourceCmd(int sourceType,
					 string sourceId,
					 BaseSurface * surface,
					 SourcesEditorWidget * sourcesEditor);
		void exec();
		void undo();

	private:
		int _sourceType;
		string _sourceId;
		BaseSurface * _surface;
		SourcesEditorWidget * _sourcesEditor;

		int _oldSourceTypeHelper;
		string _oldSourceId;

};

} // namespace piMapper
} // namespace ofx

