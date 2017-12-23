#pragma once

#include "ofMain.h"

#if OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR <= 9
// ...
#else
// TODO: include glm
#endif

namespace ofx {
namespace piMapper {

//#if OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR <= 9
class Vec2{
public:
	Vec2();
	Vec2(float $x, float $y);
	
	#if OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR <= 9
		Vec2(ofVec2f & src);
		Vec2(ofVec3f & src);
		ofVec2f toOf();
		static ofVec2f toOf(Vec2 & src);
		static vector<ofVec2f> toOf(vector<Vec2> & src);
		float distance(Vec2 & other);
	#else
		// TODO: The same for glm::vec2
		// static vector<glm::vec2> toOf(vector<Vec2> & src);
	#endif
	
	void operator=(const Vec2 & other);
	void operator=(const ofVec3f & other);
	void operator+=(Vec2 & other);
	
	Vec2 operator+(Vec2 & other);
	Vec2 operator/(Vec2 & other);
	Vec2 operator*(Vec2 & other);
	Vec2 operator-();
	Vec2 operator-(Vec2 & other);
	
	bool operator!=(Vec2 & other);
	
	float x;
	float y;
};

} // namespace piMapper
} // namespace ofx
