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
					 std::string sourceId,
					 BaseSurface * surface,
					 SourcesEditorWidget * sourcesEditor);
		void exec();
		void undo();

	private:
		int _sourceType;
		std::string _sourceId;
		BaseSurface * _surface;
		SourcesEditorWidget * _sourcesEditor;

		int _oldSourceTypeHelper;
		std::string _oldSourceId;

};

} // namespace piMapper
} // namespace ofx

