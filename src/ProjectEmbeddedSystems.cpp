//============================================================================
// Name        : ProjectEmbeddedSystems.cpp
// Author      : Thomas MAYNADIE
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Processing.h"

#include <iostream>
using namespace std;

int main()
{
	double median[uiSensorCount];

	char flag_first_start = 0;

	for(unsigned int iteration_id=0; iteration_id < uiSimCount; iteration_id++)
	{
		test(0)
		compute_median(iteration_id, median);
	}
}


