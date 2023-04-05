/*
 * kalman.h
 *
 *  Created on: 2 Mar 2020
 *      Author: candan
 */

#ifndef KALMAN_H_
#define KALMAN_H_

#define KALMAN_FILTER_ACTIVATION_LEVEL 10
#define KALMAN_FILTER_DEFAULT_MIN_CRETERIA 250

typedef struct {

//	int iKalmanLen;
	int iBufferCunter;
	int iKalmanMinCriteria;
	float fPrevData;
//	float fP;
//	float fQ;
//	float fR;
//	float fKGain;
	float ary_dDataSet[MAX_KALMAN_LEN];

}strcKalman;

//function prototypes
float dCalculateKalmanDataSet(unsigned int FilterNo, float inData);
void vInitKalman(unsigned int FilterNo,int kalman_len, float initial_data, int min_criteria);
void InitKalmanParameter(void);
#endif /* KALMAN_H_ */
