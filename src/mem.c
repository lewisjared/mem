/*
 * mem.c
 *
 *  Created on: 31/08/2013
 *      Author: jared
 */


#include "mem.h"

#include <stdio.h>

#ifdef MEM_BACKTRACE
#include "execinfo.h"
#endif


typedef struct mem_head_t {
	int tag;
	struct mem_head_t* next;
	struct mem_head_t* prev;
	size_t len;
	unsigned int count;
	void* data;
#ifdef MEM_BACKTRACE
	void* backtrace[MEM_BACKTRACE_SIZE];
	size_t backtraceCount;
#endif
} mem_head_t;

typedef struct mem_tail_t {
	int tag;
} mem_tail_t;


static mem_head_t* first = NULL;
static mem_head_t* last = NULL;
static unsigned int numAlloc = 0;
static unsigned int numCurrentlyAlloc = 0;
static size_t totalAlloc = 0;
static size_t currentAlloc = 0;

void setHeader(mem_head_t* head, size_t size);
void linkedListAddTail(mem_head_t* obj);
void linkedListRemObj(mem_head_t* obj);
void printBlock(mem_head_t* obj);


void* mem_malloc(size_t size)
{
	mem_head_t* dataPtr;
	dataPtr = (mem_head_t *) malloc( size + sizeof(mem_head_t) + sizeof(mem_tail_t));

	if (dataPtr != NULL)
	{
		setHeader(dataPtr, size);
		++numCurrentlyAlloc;
		totalAlloc += size;
		currentAlloc += size;

		// Increment pointer so returned value points to data
		return (void *) ++dataPtr;
	}

	printf("malloc returned NULL (length = %u)\n", size);
	return NULL;
}

void* mem_calloc(size_t num, size_t size)
{
	mem_head_t* dataPtr;
	dataPtr = (mem_head_t *) calloc(num, size + sizeof(mem_head_t) + sizeof(mem_tail_t));

	if (dataPtr != NULL)
	{
		setHeader(dataPtr, size);
		++numCurrentlyAlloc;
		totalAlloc += size;
		currentAlloc += size;

		// Increment pointer so returned value points to data
		return (void *) ++dataPtr;
	}

	printf("calloc returned NULL (length = %u)\n", size);
	return NULL;
}

void* mem_realloc(void* ptr, size_t size)
{
	void* dataPtr = NULL;

	if (ptr)
	{
		mem_head_t* data = ptr;
		--ptr;

		dataPtr = mem_malloc(size);
		if (dataPtr)
		{
			//Grow or shrink data as required
			if (size > data->len)
			{
				memcpy(dataPtr, ptr, data->len);
				memset(dataPtr+data->len, 0, size - data->len);
			}

			if (size < data->len)
			{
				memcpy(dataPtr, ptr, size);
			}
		}
		mem_free(ptr);
	}
	return dataPtr;
}

void mem_free(void* ptr)
{
	mem_head_t* head = (mem_head_t*) ptr;
	head--;

	linkedListRemObj(head);

	--numCurrentlyAlloc;
	currentAlloc -= head->len;

	//Check some stuff

	free(head);
}

void mem_printStats()
{
	printf("**********************************************\n");
	printf("Memory Allocation Stats\n");
	printf("**********************************************\n");
	printf("Total alloc calls:\t\t%u\n", numAlloc);
	printf("Total allocated:\t\t%u bytes\n", totalAlloc);
	printf("Currently Allocated: %u, %u bytes\n", numCurrentlyAlloc, currentAlloc);
}

void printBlock(mem_head_t* obj)
{
	printf("Block ID: %u\n", obj->count);
}

void printBT( mem_head_t* obj)
{
	if (obj)
	{
		char** strings;
		strings = backtrace_symbols(obj->backtrace, obj->backtraceCount);

		int i;
		for (i = 0; i < obj->backtraceCount; i++)
			printf("%s\n", strings[i]);
	}
}

void linkedListAddTail(mem_head_t* obj)
{
	obj->next = NULL;
	obj->prev = last;
	if (last)
		last->next = obj;
	if (first == NULL)
		first = obj;
	last = obj;
}

void linkedListRemObj(mem_head_t* obj)
{
	if (obj->prev) (obj->prev)->next = obj->next;
	if (obj->next) (obj->next) = obj->prev;

	// Check for removing first or last obj
	if (last == obj) last = obj->prev;
	if (first == obj) first = obj->next;
}

void setHeader(mem_head_t* head, size_t size)
{
	head->len = size;
	head->data = head + sizeof(mem_head_t);
	head->count = numAlloc++;

	linkedListAddTail(head);

#ifdef MEM_BACKTRACE
	head->backtraceCount = backtrace(head->backtrace, MEM_BACKTRACE_SIZE);
#endif
}
