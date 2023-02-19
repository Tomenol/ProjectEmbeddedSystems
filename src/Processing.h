/*
 * Processing.h
 *
 *  Created on: Feb 10, 2023
 *      Author: mayna
 */

#include <math.h>
#include <iostream>

#include "SortEngine.h"

#include "const.h"
#include "data.h"

#ifndef PROCESSING_H_
#define PROCESSING_H_

class ProcessingCtx
{
private:
	unsigned short raw_data[uiSensorSize][uiSensorSize];

	unsigned short median[uiSensorSize];

	unsigned short mean[uiSensorSize];
	unsigned short v_ref[uiSensorSize];
	unsigned short vs[uiSensorSize];

	unsigned short hs_count;

	SortEngine sort_engine;
public:
	ProcessingCtx() {}
	~ProcessingCtx() {}

	void set_sort_type(SortEngine::SortType _sort_type);

	void acquire_sensor_data(unsigned int _iteration_id);
	void compute_median();
	void compute_mean();
	void store_reference();
	void compute_hotspot_count();
};

#endif /* PROCESSING_H_ */
