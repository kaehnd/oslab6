#include <sys/types.h>
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

/* TODO Define additional structure definitions here */
static int fragment_count = 0;

static int free_space = 0;

static int alocated_space = 0;

static int meminit = 0;

static struct memNode
{
	int free;			  //boolean if free
	int size;			  //size of space bytes
	void *addr;			  //start address(as pointer)
	struct memNode *next; //next block addreass(as pointer)
};

static struct memNode *head;

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

	//todo lock

	head = malloc(sizeof(struct memNode));

	allocation_count = 0;

	head->size = size;
	free_space = size;

	head->free = 1;

	head->addr = start;
	head->next = NULL;

	meminit = 1;

	//todo unlock
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
	//todo lock

	struct memNode *curNode = head;
	while (curNode != NULL)
	{
		struct memNode *next = curNode->next;

		free(curNode);

		curNode = next;
	}
	free_space = 0;
	meminit = 0;
	allocation_count = 0;

	//todo unlock

	//todo destroy lock
}

static void *alloc_at_node(struct memNode *node, int nbytes)
{
	//todo lock

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

	//setup and return alloc'd node
	node->size = nbytes;
	node->free = 0;

	free_space -= nbytes;
	allocation_count++;

	//todo unlock

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
	if (meminit && free_space >= nbytes)
	{
		struct memNode *curNode = head;

		while (curNode != NULL && !curNode->free && curNode->size < nbytes)
		{
			curNode = curNode->next;
		}

		if (curNode != NULL && curNode->free && curNode->size > nbytes)
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
	if (meminit && free_space > nbytes)
	{
		struct memNode *curNode = head;
		struct memNode *biggestNode = NULL;

		while (curNode != NULL)
		{
			if (curNode->free && curNode->size > nbytes)
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
	if (meminit != 1 || free_space < nbytes)
	{
		//error
		return NULL;
	}

	struct memNode *preptr, *best, *ptr;
	preptr = head;
	best = head;
	int end = 1;
	while ((preptr->size != nbytes) && (preptr->free != 1) && end)
	{
		//if the free space is perfect set alocation and end loop
		if (preptr->size == nbytes && preptr->free)
		{
			preptr->free = 0;
			end = 0;
		} //if the pointer is a better fit than the current best point to that
		else if ((preptr->size < best->size) && (preptr->size > nbytes) && (preptr->free))
		{
			best = preptr;
		}
	}

	return preptr->addr;
}

	// static void memNode_coalesce(struct memNode * node1, struct memNode * node2)
	// {

	// 	node1->size += node2->size;
	// 	node1->next = node2->next;
	// 	free(node2);
	// 	curNode = prevNode;
		
	// }

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
	if (meminit)
	{
		struct memNode * prevNode = NULL;
		struct memNode * curNode = head;

		while(curNode!= NULL && curNode->addr != ptr)
		{
			prevNode = curNode;
			curNode = curNode->next;
		}

		if (curNode != NULL && curNode->addr == ptr && !curNode->free)
		{
			//todo lock
			//do free
			curNode->free = 1;
			free_space += curNode->size;
			allocation_count--;

			//coalesce memory
			if (prevNode != NULL && prevNode->free)
			{
				prevNode->size += curNode->size;
				prevNode->next = curNode->next;
				free(curNode);
				curNode = prevNode;
			}

			struct memNode * nextNode = curNode->next;
			if (nextNode != NULL && nextNode->free)
			{
				curNode->size += nextNode->size;
				curNode->next = nextNode->next;
				free(nextNode);				
			}
			//todo unlock
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
	return alocated_space;
}

/* get_remaining_space()
 *     Retrieve the current amount of available space in the memory manager (in bytes)
 *         (e.g. sum of all free blocks)
 *         Parameters: None
 *         Returns: int - the current number of free bytes 
 */
int get_remaining_space()
{
	return free_space;
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
