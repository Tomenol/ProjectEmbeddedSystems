/*
 * Processing.cpp
 *
 *  Created on: Feb 10, 2023
 *      Author: mayna
 */

#include "Processing.h"

void ProcessingCtx::set_sort_type(SortEngine::SortType _sort_type)
{
	this->sort_engine.setSortType(_sort_type);
}

void ProcessingCtx::acquire_sensor_data(unsigned int _iteration_id)
{
	for(unsigned int sensor_id=0; sensor_id<uiSensorCount; sensor_id++)
	{
		for(unsigned int px_id=0; px_id < uiSensorSize; px_id++)
			this->raw_data[sensor_id][px_id] = p_usSrcData[_iteration_id][sensor_id][px_id];
	}
}

void ProcessingCtx::compute_median()
{
	unsigned short tmp[uiSensorCount];

	for(unsigned int px_id=0; px_id < uiSensorSize; px_id++)
	{
		for(unsigned int sensor_id=0; sensor_id<uiSensorCount; sensor_id++)
			tmp[sensor_id] = this->raw_data[sensor_id][px_id];

		this->sort_engine.sort(tmp, uiSensorCount);

		this->median[px_id] = (unsigned short)((unsigned int)tmp[24] + (unsigned int)tmp[25])/2;
	}
}

void ProcessingCtx::compute_mean()
{
	unsigned int tmp;
	unsigned char n_elmt;

	for(unsigned char px_id=0; px_id < uiSensorSize; px_id++)
	{
		tmp = 0;
		n_elmt = 0;

		for(unsigned char sensor_id=0; sensor_id < uiSensorCount; sensor_id++)
		{
			if(abs((int)(this->raw_data[sensor_id][px_id]) - (int)(this->median[px_id])) < usGrantedError)
			{
				tmp += (unsigned int)this->raw_data[sensor_id][px_id];
				n_elmt += 1;
			}
		}

		this->mean[px_id] = tmp/n_elmt;
	}
}

void ProcessingCtx::store_reference()
{
	for(unsigned int px_id=0; px_id < uiSensorSize; px_id++)
	{
		this->v_ref[px_id] = this->mean[px_id];
	}
}

void ProcessingCtx::compute_hotspot_count()
{
	this->hs_count = 0;

	for(unsigned int px_id=0; px_id < uiSensorSize; px_id++)
	{
		this->vs[px_id] = (this->mean[px_id] - this->v_ref[px_id]);
		if(this->mean[px_id] - this->v_ref[px_id] > usHotspotDetectionThreshold)
		{
			this->hs_count += 1;
		}
	}
}
