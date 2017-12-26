#include "Vec2.h"

namespace ofx {
namespace piMapper {

Vec2::Vec2(){
	Vec2(0.0f, 0.0f);
}

Vec2::Vec2(float ix, float iy){
	x = ix;
	y = iy;
}

#if OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR <= 9
	Vec2::Vec2(ofVec2f & src){
		x = src.x;
		y = src.y;
	}
	
	ofVec2f Vec2::toOf(){
		return ofVec2f(x, y);
	}

	vector<ofVec2f> Vec2::toOf(vector<Vec2> & src){
		vector<ofVec2f> retVal;
		for(auto itm : src){
			retVal.push_back(itm.toOf());
		}
		return retVal;
	}
	
	vector<Vec2> Vec2::fromOf(vector<ofVec2f> & src){
		vector<Vec2> retVal;
		for(auto itm : src){
			retVal.push_back(Vec2(itm));
		}
		return retVal;
	}
	
	float Vec2::distance(const Vec2 & other){
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

void Vec2::operator+=(const Vec2 & other){
	x += other.x;
	y += other.y;
}

Vec2 Vec2::operator+(const Vec2 & other){
	return Vec2(x + other.x, y + other.y);
}

Vec2 Vec2::operator-(){
	return Vec2(-x, -y);
}

Vec2 Vec2::operator-(const Vec2 & other){
	return Vec2(x - other.x, y - other.y);
}

Vec2 Vec2::operator*(const Vec2 & other){
	return Vec2(x * other.x, y * other.y);
}

Vec2 Vec2::operator/(const Vec2 & other){
	return Vec2(x / other.x, y / other.y);
}

bool Vec2::operator==(const Vec2 & other){
	if(x == other.x && y == other.y){
		return true;
	}
	return false;
}

bool Vec2::operator!=(const Vec2 & other){
	if(x != other.x && y != other.y){
		return true;
	}
	return false;
}

} // namespace piMapper
} // namespace ofx
