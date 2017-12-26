#include "Vec3.h"

namespace ofx {
namespace piMapper {

Vec3::Vec3(){
	Vec3(0.0f, 0.0f, 0.0f);
}

Vec3::Vec3(float ix, float iy, float iz){
	x = ix;
	y = iy;
	z = iz;
}

#if OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR <= 9
	Vec3::Vec3(ofVec3f & src){
		x = src.x;
		y = src.y;
		z = src.z;
	}
	
	ofVec3f Vec3::toOf(){
		return ofVec3f(x, y, z);
	}
	
	std::vector<ofVec3f> Vec3::toOf(std::vector<Vec3> & src){
		std::vector<ofVec3f> retVal;
		for(auto itm : src){
			retVal.push_back(itm.toOf());
		}
		return retVal;
	}
	
	std::vector<Vec3> Vec3::fromOf(std::vector<ofVec3f> & src){
		std::vector<Vec3> retVal;
		for(auto itm : src){
			retVal.push_back(Vec3(itm));
		}
		return retVal;
	}
#else
	Vec3::Vec3(glm::vec3 & src){
		x = src.x;
		y = src.y;
		z = src.z;
	}
	
	glm::vec3 Vec3::toOf(){
		return ofVec3f(x, y, z);
	}
	
	std::vector<glm::vec3> Vec3::toOf(std::vector<Vec3> & src){
		std::vector<glm::vec3> retVal;
		for(auto itm : src){
			retVal.push_back(itm.toOf());
		}
		return retVal;
	}
	
	std::vector<Vec3> Vec3::fromOf(std::vector<glm::vec3> & src){
		std::vector<Vec3> retVal;
		for(auto itm : src){
			retVal.push_back(Vec3(itm));
		}
		return retVal;
	}
#endif

void Vec3::operator=(const Vec3 & other){
	x = other.x;
	y = other.y;
	z = other.z;
}

void Vec3::operator+=(const Vec3 & other){
	x += other.x;
	y += other.y;
	z += other.z;
}

void Vec3::operator*=(const Vec3 & other){
	x *= other.x;
	y *= other.y;
	z *= other.z;
}

void Vec3::operator*=(float n){
	x *= n;
	y *= n;
	z *= n;
}

void Vec3::operator/=(const Vec3 & other){
	x /= other.x;
	y /= other.y;
	z /= other.z;
}

void Vec3::operator/=(float n){
	x /= n;
	y /= n;
	z /= n;
}

Vec3 Vec3::operator+(const Vec3 & other){
	return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 Vec3::operator-(){
	return Vec3(-x, -y, -z);
}

Vec3 Vec3::operator-(const Vec3 & other){
	return Vec3(x - other.x, y - other.y, z - other.z);
}

Vec3 Vec3::operator*(const Vec3 & other){
	return Vec3(x * other.x, y * other.y, z * other.z);
}

Vec3 Vec3::operator*(float n){
	return Vec3(x * n, y * n, z * n);
}

Vec3 Vec3::operator/(const Vec3 & other){
	return Vec3(x / other.x, y / other.y, z / other.z);
}

Vec3 Vec3::operator/(float n){
	return Vec3(x / n, y / n, z / n);
}

bool Vec3::operator==(const Vec3 & other){
	if(x == other.x && y == other.y && z == other.z){
		return true;
	}
	return false;
}

bool Vec3::operator!=(const Vec3 & other){
	if(x != other.x && y != other.y && z != other.z){
		return true;
	}
	return false;
}

} // namespace piMapper
} // namespace ofx
