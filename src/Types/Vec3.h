#pragma once

#if OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR <= 9
#include "ofMain.h"
#else
// TODO: include glm
#endif

namespace ofx {
namespace piMapper {

class Vec3{
public:
	Vec3();
	Vec3(float $x, float $y, float $z);
	
	#if OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR <= 9
		Vec3(ofVec3f & src);
		ofVec3f toOf();
		static ofVec3f toOf(Vec3 & src);
		static vector<ofVec3f> toOf(vector<Vec3> & src);
	#else
		// TODO: The same for glm::vec2
		// static vector<glm::vec2> toOf(vector<Vec2> & src);
	#endif
	
	void operator=(const Vec3 & other);
	void operator=(const ofVec3f & other);
	
	Vec3 operator+(Vec3 & other);
	
	Vec3 operator-();
	Vec3 operator-(Vec3 & other);
	
	bool operator!=(Vec3 & other);
	
	float x;
	float y;
	float z;
};

} // namespace piMapper
} // namespace ofx
