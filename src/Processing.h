/*
 * Processing.h
 *
 *  Created on: Feb 10, 2023
 *
 *  This module defines the ProcessingCTX class which holds all the data related to the
 *  simulation of the data processing of instrument measurements.
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
	// raw measurement data
	unsigned short raw_data[uiSensorSize][uiSensorSize];

	// processing related variables
	unsigned short median[uiSensorSize];
	unsigned short mean[uiSensorSize];
	unsigned short v_ref[uiSensorSize];
	unsigned short vs[uiSensorSize];

	// output value
	unsigned short hs_count;

	// sorting algorithm used in the processing algorithm
	SortEngine sort_engine;
public:
	ProcessingCtx()
	{
		this->hs_count = 0;
	}
	~ProcessingCtx() {}

	// for simulation only
	void set_sort_type(SortEngine::SortType _sort_type);

	// processing functions
	void acquire_sensor_data(unsigned int _iteration_id);
	void compute_median();
	void compute_mean();
	void store_reference();
	void compute_hotspot_count();
};

#endif /* PROCESSING_H_ */
