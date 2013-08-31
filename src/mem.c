/*
 * mem.c
 *
 *  Created on: 31/08/2013
 *      Author: jared
 */


#include "mem.h"

#include <stdio.h>


typedef struct{

} mem_head_t;

typedef struct{

} mem_tail_t;



void* mem_malloc(size_t size)
{
	mem_head_t* dataPtr = (mem_head_t *) malloc( size + sizeof(mem_head_t) + sizeof(mem_tail_t));

	if (dataPtr == NULL)
		printf("malloc returned NULL (length = %u)\n", size);
	// Increment pointer so returned value points to data
	return (void *) dataPtr++;
}

void* mem_calloc(size_t num, size_t size)
{
	(void) num;
	(void) size;
	return NULL;
}

void* mem_realloc(void* ptr, size_t size)
{
	(void) ptr;
	(void) size;
	return NULL;
}

void mem_free(void* ptr)
{
	mem_head_t* head = (mem_head_t*) ptr;
	head--;

	//Check some stuff
	printf("Freeing memory\n");

	free(head);
}
