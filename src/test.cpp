/*
 * test.cpp
 *
 *  Created on: Feb 10, 2023
 *      Author: mayna
 */

#include "test.h"

int test(const char *testName, int testId) {
	int static testCounter = 0;
	return testCounter++;
}
