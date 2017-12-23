#include "Vec3.h"

namespace ofx {
namespace piMapper {

Vec3::Vec3(){
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Vec3::Vec3(float $x, float $y, float $z){
	x = $x;
	y = $y;
	z = $z;
}

#if OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR <= 9
	Vec3::Vec3(ofVec3f & src){
		x = src.x;
		y = src.y;
		z = src.z;
	}
	
	ofVec3f Vec3::toOf(){
		ofVec3f(x, y, z);
	}
	
	ofVec3f toOf(Vec3 & src){
		return ofVec3f(src.x, src.y, src.z);
	}

	vector<ofVec3f> toOf(vector<Vec3> & src){
		vector<ofVec3f> dst;
		for(auto v : src){
			dst.push_back(ofVec3f(v.x, v.y, v.z));
		}
		return dst;
	}
#else
		// TODO: The same for glm::vec2
#endif

void Vec3::operator=(const Vec3 & other){
	x = other.x;
	y = other.y;
	z = other.z;
}

void Vec3::operator=(const ofVec3f & other){
	x = other.x;
	y = other.y;
	z = other.z;
}

Vec3 Vec3::operator+(Vec3 & other){
	return Vec3(
		x + other.x,
		y + other.y,
		z + other.z);
}

Vec3 Vec3::operator-(){
	return Vec3(-x, -y, -z);
}

Vec3 Vec3::operator-(Vec3 & other){
	return Vec3(
		x - other.x,
		y - other.y,
		z - other.z);
}

bool Vec3::operator!=(Vec3 & other){
	if(x == other.x && y == other.y && z == other.z){
		return false;
	}
	return true;
}

} // namespace piMapper
} // namespace ofx
