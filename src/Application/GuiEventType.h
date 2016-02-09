#pragma once

namespace ofx {
namespace piMapper {

struct GuiEventType {
	enum {
		SURFACE_HIT,
		SURFACE_DRAGGED,
		SURFACE_RELEASED,
		HANDLE_HIT,
		HANDLE_DRAGGED,
		HANDLE_RELEASED
	};
};

} // namespace piMapper
} // namespace ofx