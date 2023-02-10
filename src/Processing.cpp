/*
 * Processing.cpp
 *
 *  Created on: Feb 10, 2023
 *      Author: mayna
 */

#include "Processing.h"

void compute_median(unsigned int _iteration_id, double *_median)
{
	SortEngine sort_engine;

	for(char sensor_id=0; sensor_id < uiSensorCount; sensor_id++)
	{
		sort_engine.sort(p_usSrcData[_iteration_id][sensor_id], uiSensorSize);

		_median[sensor_id] = (double)(p_usSrcData[_iteration_id][sensor_id][49] + p_usSrcData[_iteration_id][sensor_id][50])/2;
	}
}
