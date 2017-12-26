#pragma once

#if OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR <= 9
	#include "ofVec3f.h"
#else
	// TODO: include glm
#endif

namespace ofx {
namespace piMapper {

class Vec3{
public:
	Vec3();
	Vec3(float ix, float iy, float iz);

	// TODO: achieve this with templates
	#if OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR <= 9
		Vec3(ofVec3f & src);
		ofVec3f toOf();
		static vector<ofVec3f> toOf(vector<Vec3> & src);
		static vector<Vec3> fromOf(vector<ofVec3f> & src);
	#else
		// TODO: Vec3(glm::vec3 & src);
	#endif
	
	void operator=(const Vec3 & other);
	void operator+=(const Vec3 & other);
	void operator*=(const Vec3 & other);
	void operator*=(float n);
	void operator/=(const Vec3 & other);
	void operator/=(float n);
	Vec3 operator+(const Vec3 & other);
	Vec3 operator-();
	Vec3 operator-(const Vec3 & other);
	Vec3 operator*(const Vec3 & other);
	Vec3 operator*(float n);
	Vec3 operator/(const Vec3 & other);
	Vec3 operator/(float n);
	bool operator==(const Vec3 & other);
	bool operator!=(const Vec3 & other);
	
	float x;
	float y;
	float z;
};

} // namespace piMapper
} // namespace ofx
