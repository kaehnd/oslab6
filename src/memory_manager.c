#include <sys/types.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "memory_manager.h"

/* 
 * Using static causes the compiler to
 * limit visibility of the varibles to this file only
 * This can be used to simulate 'private' variables in c
 */
static int allocation_count = 0;

static int fragment_count = 0;

static int allocated_space = 0;

static int meminit = 0;

static int total_space = 0;

struct memNode
{
	int free;			  //boolean if free
	int size;			  //size of space bytes
	void *addr;			  //start address(as pointer)
	struct memNode *next; //next block addreass(as pointer)
};

static struct memNode *head;

static pthread_mutex_t memLock;

/* mmInit()
 *     Initialize the memory manager to "manage" the given location
 *     in memory with the specified size.
 *         Parameters: start - the start of the memory to manage
 *                     size - the size of the memory to manage
 *         Returns: void
 */
void mmInit(void *start, int size)
{
	//setup lock
	pthread_mutex_init(&memLock, NULL);

	pthread_mutex_lock(&memLock);
	//critical section
	head = malloc(sizeof(struct memNode));

	allocation_count = 0;
	total_space = size;
	allocated_space = 0;
	fragment_count = 1;

	head->size = size;

	head->free = 1;

	head->addr = start;
	head->next = NULL;

	meminit = 1;

	pthread_mutex_unlock(&memLock);
}

/* mmDestroy()
 *     Cleans up any storage used by the memory manager
 *     After a call to mmDestroy:
 *         all allocated spaces become invalid
 *         future allocation attempts fail
 *         future frees result in segmentation faults
 *     NOTE: after a call to mmDestroy a call to mmInit
 *           reinitializes the memory manager to allow allocations
 *           and frees
 *         Parameters: None
 *         Returns: void
 */
void mmDestroy()
{
	if (meminit != 1)
	{
		return;
	}

	pthread_mutex_lock(&memLock);

	struct memNode *curNode = head;
	while (curNode != NULL)
	{
		//make buffer ponter to the next
		struct memNode *next = curNode->next;
		//free the current node
		free(curNode);
		//pont to the next node
		curNode = next;
	}
	total_space = 0;
	meminit = 0;
	allocation_count = 0;
	//unlock and destroy the mutex
	pthread_mutex_unlock(&memLock);

	pthread_mutex_destroy(&memLock);
}

static void *alloc_at_node(struct memNode *node, int nbytes)
{
	pthread_mutex_lock(&memLock);

	//setup new node if size not equal
	if (node->size != nbytes)
	{
		struct memNode *next = node->next; //save for later

		node->next = malloc(sizeof(struct memNode));
		node->next->addr = node->addr + nbytes;
		node->next->free = 1;
		node->next->size = node->size - nbytes;
		node->next->next = next;
	}
	else
	{
		fragment_count--;
	}

	//setup and return alloc'd node
	node->size = nbytes;
	node->free = 0;

	allocated_space += nbytes;
	allocation_count++;

	pthread_mutex_unlock(&memLock);

	return node->addr;
}

/* mymalloc_ff()
 *     Requests a block of memory be allocated using 
 *         first fit placement algorithm
 *     The memory manager must be initialized (mmInit)
 *         for this call to succeed
 *         Parameters: nbytes - the number of bytes in the requested memory
 *         Returns: void* - a pointer to the start of the allocated space
 */
void *mymalloc_ff(int nbytes)
{
	if (meminit && (total_space - allocated_space) >= nbytes)
	{
		struct memNode *curNode = head;

		while (curNode != NULL && (!curNode->free || curNode->size < nbytes))
		{
			curNode = curNode->next;
		}

		if (curNode != NULL && curNode->free && curNode->size >= nbytes)
		{
			return alloc_at_node(curNode, nbytes);
		}
	}
	return NULL;
}

/* mymalloc_wf()
 *     Requests a block of memory be allocated using 
 *         worst fit placement algorithm
 *     The memory manager must be initialized (mmInit)
 *         for this call to succeed
 *         Parameters: nbytes - the number of bytes in the requested memory
 *         Returns: void* - a pointer to the start of the allocated space
 */
void *mymalloc_wf(int nbytes)
{
	if (meminit && (total_space - allocated_space) >= nbytes)
	{
		struct memNode *curNode = head;
		struct memNode *biggestNode = NULL;

		while (curNode != NULL)
		{
			if (curNode->free && curNode->size >= nbytes)
			{
				biggestNode = biggestNode == NULL || curNode->size > biggestNode->size ? curNode : biggestNode;
			}
			curNode = curNode->next;
		}

		if (biggestNode != NULL)
		{
			return alloc_at_node(biggestNode, nbytes);
		}
	}
	return NULL;
}

/* mymalloc_bf()
 *     Requests a block of memory be allocated using 
 *         best fit placement algorithm
 *     The memory manager must be initialized (mmInit)
 *         for this call to succeed
 *         Parameters: nbytes - the number of bytes in the requested memory
 *         Returns: void* - a pointer to the start of the allocated space
 */
void *mymalloc_bf(int nbytes)
{
	if (meminit != 1 || (total_space - allocated_space) < nbytes)
	{
		//error
		return NULL;
	}

	struct memNode *best, *ptr, *buf;

	ptr = head;

	best = NULL;
	buf = NULL;

	int bestSize = (total_space - allocated_space); //for general largest possible node

	while (best == NULL && ptr != NULL)
	{
		//if the free space is perfect set alocation and end loop
		if (ptr->size == nbytes && ptr->free)
		{
			best = ptr;
		} //if the pointer is a better fit than the current best point to that
		else if ((ptr->size <= bestSize) && (ptr->size > nbytes) && (ptr->free))
		{
			//save location
			buf = ptr;
			//update size
			bestSize = buf->size;
		}
		//if we reached the end and found no exact put it in the smallest free node
		if (ptr->next == NULL && best == NULL)
		{
			best = buf;
		}
		ptr = ptr->next;
	}

	//add node into structure
	return best == NULL ? NULL : alloc_at_node(best, nbytes);
}

/* myfree()
 *     Requests a block of memory be freed and the storage made
 *         available for future allocations
 *     The memory manager must be initialized (mmInit)
 *         for this call to succeed
 *         Parameters: ptr - a pointer to the start of the space to be freed
 *         Returns: void
 *         Signals a SIGSEGV if a free is not valid
 *             - memory manager is not initialized
 *             - memory manager has been destroyed
 *             - ptr is not allocated (e.g. double free)
 */
void myfree(void *ptr)
{
	if (meminit) //if its initialized
	{
		struct memNode *prevNode = NULL;
		struct memNode *curNode = head;
		//find node
		while (curNode != NULL && curNode->addr != ptr)
		{
			prevNode = curNode;
			curNode = curNode->next;
		}
		//if node found, addr is right, and its not already free
		if (curNode != NULL && curNode->addr == ptr && !curNode->free)
		{
			pthread_mutex_lock(&memLock);
			//do free
			curNode->free = 1;
			allocated_space -= curNode->size;
			fragment_count++;

			//coalesce memory
			if (prevNode != NULL && prevNode->free)
			{
				prevNode->size += curNode->size;
				prevNode->next = curNode->next;
				free(curNode);
				curNode = prevNode;
				fragment_count--;
			}

			struct memNode *nextNode = curNode->next;
			if (nextNode != NULL && nextNode->free)
			{
				curNode->size += nextNode->size;
				curNode->next = nextNode->next;
				free(nextNode);
				fragment_count--;
			}
			pthread_mutex_unlock(&memLock);
			return;
		}
	}

	//segfault
	kill(getpid(), SIGSEGV);
}

/* get_allocated_space()
 *     Retrieve the current amount of space allocated by the memory manager (in bytes)
 *         Parameters: None
 *         Returns: int - the current number of allocated bytes 
 */
int get_allocated_space()
{
	return allocated_space;
}

/* get_remaining_space()
 *     Retrieve the current amount of available space in the memory manager (in bytes)
 *         (e.g. sum of all free blocks)
 *         Parameters: None
 *         Returns: int - the current number of free bytes 
 */
int get_remaining_space()
{
	return total_space - allocated_space;
}

/* get_fragment_count()
 *     Retrieve the current amount of free blocks (i.e. the count of all the block, not the size)
 *         Parameters: None
 *         Returns: int - the current number of free blocks
 */
int get_fragment_count()
{
	return fragment_count;
}

/* get_mymalloc_count()
 *     Retrieve the number of successfull malloc calls (for all placement types)
 *         Parameters: None
 *         Returns: int - the total number of successfull mallocs
 */
int get_mymalloc_count()
{
	return allocation_count;
}
