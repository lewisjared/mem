/*
 * testCpp.cpp
 *
 *  Created on: 31/08/2013
 *      Author: jared
 */

#include "mem.h"
#include "stdlib.h"

#define ALLOC_SIZE 100

class TestClass
{
	int i;
};

int main ()
{
	void *dat = malloc(ALLOC_SIZE);
	free(dat);

	TestClass* cls = new TestClass();

	char* str = new char[10];
	mem_printStats();
	delete[] str;
	mem_printStats();
	delete cls;
	mem_printStats();
}
