/*
 * Processing.cpp
 *
 *  Created on: Feb 10, 2023
 *      Author: mayna
 */

#include "Processing.h"

void ProcessingCtx::set_sort_type(SortEngine::SortType _sort_type)
/*
 * Selects the sorting engine (used for simulations only).
 */
{
	this->sort_engine.setSortType(_sort_type);
}

void ProcessingCtx::acquire_sensor_data(unsigned int _iteration_id)
/*
 * Simulates the data acquisition from the DPRAM (used for simulations only).
 */
{
	// copies the measurement data from one array to an other to simulate the
	// data acquisition & transfer from the DPRAM to the SDRAM.
	for(unsigned char sensor_id=0; sensor_id<uiSensorCount; sensor_id++)
	{
		for(unsigned char px_id=0; px_id < uiSensorSize; px_id++)
			this->raw_data[sensor_id][px_id] = p_usSrcData[_iteration_id][sensor_id][px_id];
	}
}

void ProcessingCtx::compute_median()
/*
 * Computes the median of the measurements along all sensors.
 */
{
	// temp array used to store the data to be sorted
	unsigned short tmp[uiSensorCount];

	for(unsigned char px_id=0; px_id < uiSensorSize; px_id++)
	{
		// compute the mean value of a given pixel along all sensors
		for(unsigned char sensor_id=0; sensor_id<uiSensorCount; sensor_id++)
			tmp[sensor_id] = this->raw_data[sensor_id][px_id];

		this->sort_engine.sort(tmp, uiSensorCount);

		// Here the median is defined as the mean of the two central values (50 is even)
		this->median[px_id] = (unsigned short)((unsigned int)tmp[(int)(uiSensorCount/2 - 1)] + (unsigned int)tmp[(int)(uiSensorCount/2)])/2;
	}
}

void ProcessingCtx::compute_mean()
/*
 * Computes the mean of the measurements along all sensors.
 *
 * Note : Removes outliers (comparison to the median).
 */
{
	unsigned int tmp; 		// tmp value used to store the sum of all values, must be int to not overflow
	unsigned char n_elmt;	// number of elements kept (not outliers)

	for(unsigned char px_id=0; px_id < uiSensorSize; px_id++)
	{
		// reset values for each pixel
		tmp = 0;
		n_elmt = 0;

		for(unsigned char sensor_id=0; sensor_id < uiSensorCount; sensor_id++)
		{
			// compare to distance with the median to the threshold, if less, then the value is not an outliers
			if(abs((int)(this->raw_data[sensor_id][px_id]) - (int)(this->median[px_id])) < usGrantedError)
			{
				tmp += (unsigned int)this->raw_data[sensor_id][px_id];
				n_elmt += 1;
			}
		}

		// compute the mean
		this->mean[px_id] = (unsigned short)(tmp/n_elmt);
	}
}

void ProcessingCtx::store_reference()
/*
 * Stores the reference vector during the first iteration
 */
{
	for(unsigned char px_id=0; px_id < uiSensorSize; px_id++)
	{
		this->v_ref[px_id] = this->mean[px_id];
	}
}

void ProcessingCtx::compute_hotspot_count()
/*
 * Computes the number of hotspots by comparing the mean at time t to the reference mean vector (1st computation).
 */
{
	this->hs_count = 0;

	for(unsigned char px_id=0; px_id < uiSensorSize; px_id++)
	{
		// In the original algorithm, the difference is clipped to zero, but
		// since the threshold is greater than 0, we directly compare the value to the
		// threshold.
		if((int)this->mean[px_id] - (int)this->v_ref[px_id] > usHotspotDetectionThreshold)
		{
			this->hs_count += 1;
		}
	}
}
