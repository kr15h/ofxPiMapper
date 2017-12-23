#include "Vec2.h"

namespace ofx {
namespace piMapper {

Vec2::Vec2(){
	x = 0.0f;
	y = 0.0f;
}

Vec2::Vec2(float $x, float $y){
	x = $x;
	y = $y;
}

#if OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR <= 9
	Vec2::Vec2(ofVec2f & src){
		x = src.x;
		y = src.y;
	}
	
	Vec2::Vec2(ofVec3f & src){
		x = src.x;
		y = src.y;
	}
	
	ofVec2f Vec2::toOf(){
		return ofVec2f(x, y);
	}
	
	ofVec2f Vec2::toOf(Vec2 & src){
		return ofVec2f(src.x, src.y);
	}

	vector<ofVec2f> Vec2::toOf(vector<Vec2> & src){
		vector<ofVec2f> dst;
		for(auto v : src){
			dst.push_back(ofVec2f(v.x, v.y));
		}
		return dst;
	}
	
	float Vec2::distance(Vec2 & other){
		ofVec2f v1(x, y);
		ofVec2f v2(other.x, other.y);
		return v1.distance(v2);
	}
#else
		// TODO: The same for glm::vec2
#endif

void Vec2::operator=(const Vec2 & other){
	x = other.x;
	y = other.y;
}

void Vec2::operator=(const ofVec3f & other){
	x = other.x;
	y = other.y;
}

void Vec2::operator+=(Vec2 & other){
	x += other.x;
	y += other.y;
}

Vec2 Vec2::operator+(Vec2 & other){
	return Vec2(x + other.x, y + other.y);
}

Vec2 Vec2::operator/(Vec2 & other){
	return Vec2(x / other.x, y / other.y);
}

Vec2 Vec2::operator*(Vec2 & other){
	return Vec2(x * other.x, y * other.y);
}

Vec2 Vec2::operator-(){
	return Vec2(-x, -y);
}

Vec2 Vec2::operator-(Vec2 & other){
	return Vec2(x - other.x, y - other.y);
}

bool Vec2::operator!=(Vec2 & other){
	if(x == other.x && y == other.y){
		return false;
	}
	return true;
}

} // namespace piMapper
} // namespace ofx
