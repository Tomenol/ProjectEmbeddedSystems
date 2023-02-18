//============================================================================
// Name        : ProjectEmbeddedSystems.cpp
// Author      : Thomas MAYNADIE
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Processing.h"
#include "test.h"

#include <iostream>
using namespace std;

void sim_heapsort();
void sim_quicksort();
void simulation();
int main();

ProcessingCtx ctx;

int main()
{
	// simulate computations using quicksort
	sim_quicksort();

	// simulate computations using heapsort
	sim_heapsort();
}

void sim_heapsort()
{
	// reset context
	new (&ctx) ProcessingCtx();
	ctx.set_sort_type(SortEngine::SortType::HEAP);

	test("sim_heapsort", 0);

	// start simulation
	simulation();
}

void sim_quicksort()
{
	// reset context
	new (&ctx) ProcessingCtx();
	ctx.set_sort_type(SortEngine::SortType::QUICK);

	test("sim_quicksort", 0);

	// start simulation
	simulation();
}

void simulation()
{
	// start simulation debug point
	test("start", 0);

	for(unsigned int iteration_id=0; iteration_id < uiSimCount; iteration_id++)
	{
		test("reset", 0);

		// compute median
		ctx.compute_median(iteration_id);
		test("compute_median", 1);

		// compute mean (remove outliers)
		ctx.compute_mean(iteration_id);
		test("compute_mean", 1);

		if(iteration_id == 0)
		{
			ctx.store_reference(iteration_id);
			test("store_reference", 1);
		}
		else
		{
			// compute hotspots
			ctx.compute_hotspot_count(iteration_id);
			test("compute_hotspot_count", 1);
		}
	}
}
