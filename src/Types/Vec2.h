#pragma once

#include <vector>

#if OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR <= 9
	#include "ofVec2f.h"
#else
	#include "glm/vec2.hpp"
#endif

namespace ofx {
namespace piMapper {

class Vec2{
public:
	Vec2();
	Vec2(float ix, float iy);
	
	// TODO: Achieve this with templates
	#if OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR <= 9
		Vec2(ofVec2f & src);
		ofVec2f toOf();
		static std::vector<ofVec2f> toOf(std::vector<Vec2> & src);
		static std::vector<Vec2> fromOf(std::vector<ofVec2f> & src);
	#else
		Vec2(glm::vec2 & src);
		glm::vec2 toOf();
		static std::vector<glm::vec2> toOf(std::vector<Vec2> & src);
		static std::vector<Vec2> fromOf(std::vector<glm::vec2> & src);
	#endif
	
	float distance(const Vec2 & other);
	
	void operator=(const Vec2 & other);
	void operator+=(const Vec2 & other);
	Vec2 operator+(const Vec2 & other);
	Vec2 operator-();
	Vec2 operator-(const Vec2 & other);
	Vec2 operator*(const Vec2 & other);
	Vec2 operator/(const Vec2 & other);
	bool operator==(const Vec2 & other);
	bool operator!=(const Vec2 & other);
	
	float x;
	float y;
};

} // namespace piMapper
} // namespace ofx
