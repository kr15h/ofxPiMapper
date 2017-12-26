#include "Vec2.h"

#if OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR > 9
	#include "glm/geometric.hpp"
#endif

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

	std::vector<ofVec2f> Vec2::toOf(std::vector<Vec2> & src){
		std::vector<ofVec2f> retVal;
		for(auto itm : src){
			retVal.push_back(itm.toOf());
		}
		return retVal;
	}
	
	std::vector<Vec2> Vec2::fromOf(std::vector<ofVec2f> & src){
		std::vector<Vec2> retVal;
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
	Vec2::Vec2(glm::vec2 & src){
		x = src.x;
		y = src.y;
	}
	
	glm::vec2 Vec2::toOf(){
		return glm::vec2(x, y);
	}

	std::vector<glm::vec2> Vec2::toOf(std::vector<Vec2> & src){
		std::vector<glm::vec2> retVal;
		for(auto itm : src){
			retVal.push_back(itm.toOf());
		}
		return retVal;
	}
	
	std::vector<Vec2> Vec2::fromOf(std::vector<glm::vec2> & src){
		std::vector<Vec2> retVal;
		for(auto itm : src){
			retVal.push_back(Vec2(itm));
		}
		return retVal;
	}
	
	float Vec2::distance(const Vec2 & other){
		glm::vec2 v1(x, y);
		glm::vec2 v2(other.x, other.y);
		
		return glm::distance(v1, v2);
	}
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
