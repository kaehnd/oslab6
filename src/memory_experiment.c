/* 
 * memory_experiment.c
 *
 * James Rector and Daniel Kaehn
 * CS 3841 Lab 6: Memory Manager
 * 10/25/2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include"memory_manager.h"

#define MY_HEAP_SIZE 10000
#define DEV 10

#ifdef RAND_MAX
#undef RAND_MAX
#endif

#define RAND_MAX 25

void free_random_bytes(char*** ptr_in) 
{
    char** ptr = *ptr_in;
    //free every other byte
    for(int i = (MY_HEAP_SIZE/DEV)-1; i >= 0; i--)
    {
        if((rand()%2 == 0) && ptr[i] != NULL) 
        {
            myfree(ptr[i]);
            ptr[i] = NULL;
        }
    }
    return;
}

void free_all_bytes(char*** ptr_in) 
{
    char** ptr = *ptr_in;
    //free every other byte
    for(int i = (MY_HEAP_SIZE/DEV)-1; i >= 0; i--)
    {
        if(ptr[i] != NULL) 
        {
            myfree(ptr[i]);
            ptr[i] = NULL;
        }
    }
    return;
}


int main()
{
	char my_heap[MY_HEAP_SIZE];
	mmInit(my_heap, MY_HEAP_SIZE);
	
	printf("initial -- Available Memory: %d, Fragment Count: %d, Successful Alocations: %d\n", get_remaining_space(), get_fragment_count(), get_mymalloc_count());
	
	char **ptr = malloc(sizeof(char*) * (MY_HEAP_SIZE/DEV));
    char ***ptr1 = &ptr;
    
    for(int i = (MY_HEAP_SIZE/DEV)-1; i >= 0; i--) {
        ptr[i] = NULL;
    }
    
    // attempt one at making as many fragments as possible w/ff
    for(int i = (MY_HEAP_SIZE/DEV)-1; i >= 0; i--)
    {
        ptr[i] = mymalloc_ff(((rand()%RAND_MAX)+1));
    }
    //free every other byte
    free_random_bytes(ptr1);

    for(int i = (MY_HEAP_SIZE/DEV)-1; i >= 0; i--)
    {
        ptr[i] = mymalloc_ff(((rand()%RAND_MAX)+1));
    }

    free_random_bytes(ptr1);
	printf("t1 ff -- Available Memory: %d, Fragment Count: %d, Successful Alocations: %d\n", get_remaining_space(), get_fragment_count(), get_mymalloc_count());
	//free the rest
    free_all_bytes(ptr1);


	// attempt one at making as many fragments as possible w/bf
    for(int i = (MY_HEAP_SIZE/DEV)-1; i >= 0; i--)
    {
        ptr[i] = mymalloc_bf(((rand()%RAND_MAX)+1));
    }
    //free every other byte
    free_random_bytes(ptr1);

    for(int i = (MY_HEAP_SIZE/DEV)-1; i >= 0; i--)
    {
        ptr[i] = mymalloc_bf(((rand()%RAND_MAX)+1));
    }

    free_random_bytes(ptr1);
	printf("t1 bf -- Available Memory: %d, Fragment Count: %d, Successful Alocations: %d\n", get_remaining_space(), get_fragment_count(), get_mymalloc_count());
	//free the rest
    free_all_bytes(ptr1);
    

	// attempt one at making as many fragments as possible w/wf
    for(int i = (MY_HEAP_SIZE/DEV)-1; i >= 0; i--)
    {
        ptr[i] = mymalloc_wf(((rand()%RAND_MAX)+1));
    }
    //free every other byte
    free_random_bytes(ptr1);
    
    for(int i = (MY_HEAP_SIZE/DEV)-1; i >= 0; i--)
    {
        ptr[i] = mymalloc_wf(((rand()%RAND_MAX)+1));
    }

    free_random_bytes(ptr1);
	printf("t1 wf -- Available Memory: %d, Fragment Count: %d, Successful Alocations: %d\n", get_remaining_space(), get_fragment_count(), get_mymalloc_count());
	//free the rest
    free_all_bytes(ptr1);

    free(ptr);
	mmDestroy();
	
	return 0;
}
