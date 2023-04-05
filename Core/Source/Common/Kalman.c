/*
 * Kalman.c
 *
 *  Created on: Jul 20, 2022
 *      Author: Sezgin Berber
 */
#include "Registers.h"
#include "PlcDefinition.h"
#include "kalman.h"

extern strcKalman mKalmanFilter[AI_CHANNEL_COUNT];
extern strcPLC Plc;

float dCalculateKalmanDataSet(unsigned int FilterNo, float inData)
{
	int i = 0;

	if(mKalmanFilter[FilterNo].iBufferCunter == 0)
	  {
		if (inData < mKalmanFilter[FilterNo].iKalmanMinCriteria)
		  return inData;

		for(i=0;i<(*Plc.Peripheral.AnalogInput.KalmanPar.Len - 1);i++)
			mKalmanFilter[FilterNo].ary_dDataSet[i] = inData;

		mKalmanFilter[FilterNo].iBufferCunter = *Plc.Peripheral.AnalogInput.KalmanPar.Len - 1;
		return inData;
	  }

	float prevData=0;
	float p=10, q=0.0001, r=0.05, kGain=0;

	p 		= *Plc.Peripheral.AnalogInput.KalmanPar.fP  ;
	q 		= *Plc.Peripheral.AnalogInput.KalmanPar.fQ ;
	r 		= *Plc.Peripheral.AnalogInput.KalmanPar.fR;
	kGain 	= *Plc.Peripheral.AnalogInput.KalmanPar.fKGain;

	//add item last
	mKalmanFilter[FilterNo].ary_dDataSet[*Plc.Peripheral.AnalogInput.KalmanPar.Len - 1] = inData;

	for(i=0;i<*Plc.Peripheral.AnalogInput.KalmanPar.Len;i++)
	  {
		inData = mKalmanFilter[FilterNo].ary_dDataSet[i];
		//Kalman filter function start*******************************
		  p = p+q;
		  kGain = p/(p+r);

		  inData = prevData+(kGain*(inData-prevData));
		  p = (1-kGain)*p;
		prevData = inData;
		  //Kalman filter function stop********************************
	  }

	//shif buffer left 1
	for(i=0;i<(*Plc.Peripheral.AnalogInput.KalmanPar.Len - 1); i++)
	  {
		  mKalmanFilter[FilterNo].ary_dDataSet[i] = mKalmanFilter[FilterNo].ary_dDataSet[i+1];
	  }

	return inData;
}

void vInitKalman(unsigned int FilterNo,int kalman_len, float initial_data, int min_criteria)
{


	mKalmanFilter[FilterNo].iKalmanMinCriteria=min_criteria;

	int i = 0;
	for(i=0;i<kalman_len;i++)
		mKalmanFilter[FilterNo].ary_dDataSet[i] = initial_data;

}

void InitKalmanParameter(void)
{
	unsigned short FilterNo;
	int kalman_len;
	kalman_len = *Plc.Peripheral.AnalogInput.KalmanPar.Len;
	if(kalman_len > MAX_KALMAN_LEN)
		{
			kalman_len = MAX_KALMAN_LEN;
			*Plc.Peripheral.AnalogInput.KalmanPar.Len = MAX_KALMAN_LEN;
		}


	for(FilterNo=0; FilterNo<AI_CHANNEL_COUNT; FilterNo++)
		{
			vInitKalman(FilterNo,kalman_len,0,0);
		}
}

