/*
 * ofxCvKalman.h
 *
 *  Created on: 23-jun-2009
 *      Author: art
 */

#ifndef OFXCVKALMAN_H_
#define OFXCVKALMAN_H_

#include "ofxOpenCv.h"

class ofxCvKalman {
public:
	ofxCvKalman(float initial);
	virtual ~ofxCvKalman();

	float correct(float nextPoint);

	CvKalman * kalman;
	CvMat* state;
	CvMat* process_noise;
	CvMat* measurement;
	CvRandState rng;

};

#endif /* OFXCVKALMAN_H_ */
