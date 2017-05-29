/*
 * ofxCvKalman.cpp
 *
 *  Created on: 23-jun-2009
 *      Author: art
 */

#include "ofxCvKalman.h"
#include "ofMain.h"

// Transition matrix ‘A’ describes relationship between
// model parameters at step k and at step k+1 (this is
// the “dynamics” in our model)
//
const float A[] = { 1, 1, 0, 1 };


ofxCvKalman::ofxCvKalman(float initial) {

	kalman = cvCreateKalman( 1, 1, 0 );
	measurement = cvCreateMat( 1, 1, CV_32FC1 );
	cvZero( measurement );

	//kalman->transition_matrix = cvCreateMat( 4, 1, CV_32FC1 );
	//cvSetIdentity( kalman->transition_matrix, cvRealScalar(1) );
	memcpy( kalman->transition_matrix->data.fl, A, sizeof(A));
	cvSetIdentity( kalman->measurement_matrix, cvRealScalar(1) );
	cvSetIdentity( kalman->process_noise_cov, cvRealScalar(1e-8) );
	cvSetIdentity( kalman->measurement_noise_cov, cvRealScalar(1e-8) );
	cvSetIdentity( kalman->error_cov_post, cvRealScalar(1e-5));

	kalman->state_post->data.fl[0]=initial;


}

ofxCvKalman::~ofxCvKalman() {
	cvReleaseKalman(&kalman);
	cvReleaseMat(&measurement);
}


float ofxCvKalman::correct(float next){

	//state->data.fl[0]=next;

	/* predict point position */
	const CvMat* prediction = cvKalmanPredict( kalman, 0 );
	//float predict = prediction->data.fl[0];


	/* generate measurement */
	measurement->data.fl[0]=next;


	/* adjust Kalman filter state */
	const CvMat* correction = cvKalmanCorrect( kalman, measurement );


	return correction->data.fl[0];

}
