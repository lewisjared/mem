/*
 * mem.h
 *
 *  Created on: 31/08/2013
 *      Author: jared
 */

#ifndef MEM_H_
#define MEM_H_

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

void* mem_malloc(size_t size);
void* mem_calloc(size_t num, size_t size);
void* mem_realloc(void* ptr, size_t size);
void mem_free(void* ptr);

void mem_printStats();

/**
 * Override the new, delete and delete[] if c++
 */
#ifdef __cplusplus
	void* operator new(size_t size)
	{
		return mem_malloc(size);
	}

	void* operator new[](size_t size)
	{
		return mem_malloc(size);
	}

	void operator delete(void* ptr)
	{
		mem_free(ptr);
	}

	void operator delete[](void* ptr)
	{
		mem_free(ptr);
	}

#endif /*__cplusplus */

#ifdef __cplusplus
}
#endif

#endif /* MEM_H_ */
