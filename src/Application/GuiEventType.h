#pragma once

namespace ofx {
namespace piMapper {

struct GuiEventType {
	enum {
		SURFACE_HIT,
		SURFACE_DRAGGED,
		SURFACE_RELEASED,
		JOINT_PRESSED,
		JOINT_RELEASED,
		JOINT_DRAGGED
	};
};

} // namespace piMapper
} // namespace ofx