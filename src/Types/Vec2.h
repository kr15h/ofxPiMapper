#pragma once

#if OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR <= 9
	#include "ofVec2f.h"
#else
	// TODO: include glm
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
		static vector<ofVec2f> toOf(vector<Vec2> & src);
		static vector<Vec2> fromOf(vector<ofVec2f> & src);
	#else
		// TODO: glm
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
