/*
 *  HomographyHelper
 *  Created by Elliot Woods on 26/11/2010.
 *  Edited by Krisjanis Rijnieks on 23/01/2016
 *
 *  Based entirely on arturo castro's homography implementation
 *  Created 08/01/2010, arturo castro
 *
 *	http://www.openframeworks.cc/forum/viewtopic.php?f=9&t=3121
 */

#pragma once

#include "ofMatrix4x4.h"

namespace ofx {
namespace piMapper {

class HomographyHelper {
	public:
		static void gaussian_elimination(float *input, int n);
		static void findHomography(float src[4][2], float dst[4][2], float homography[16]);
};

}
}
