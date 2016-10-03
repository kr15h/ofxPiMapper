#pragma once

namespace ofx {
namespace piMapper {

struct SurfaceType {
	enum {
		TRIANGLE_SURFACE,
		QUAD_SURFACE,
		GRID_WARP_SURFACE,
		HEXAGON_SURFACE
	};
};

} // namespace piMapper
} // namespace ofx