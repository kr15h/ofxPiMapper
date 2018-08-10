// SetVideoSourceCmd
// Set selected surface video source undoable command
// Created by Krisjanis Rijnieks 2018-08-10

#pragma once

#include "BaseCmd.h"
#include "BaseSurface.h"
#include "SourcesEditorWidget.h"

namespace ofx {
namespace piMapper {

class SourcesEditorWidget;

class SetVideoSourceCmd : public BaseUndoCmd {

	public:
		SetVideoSourceCmd(std::string sourceId,
					 bool loop,
					 BaseSurface * surface,
					 SourcesEditorWidget * sourcesEditor);
		void exec();
		void undo();

	private:
		std::string _sourceId;
		bool _loop;
		BaseSurface * _surface;
		SourcesEditorWidget * _sourcesEditor;

		int _oldSourceTypeHelper;
		std::string _oldSourceId;

};

} // namespace piMapper
} // namespace ofx

