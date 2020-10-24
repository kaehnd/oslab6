#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "memory_manager.h"

#define MY_HEAP_SIZE 100
#define MOD 2

int main2()
{
	char my_heap[MY_HEAP_SIZE];
	mmInit(my_heap, MY_HEAP_SIZE);
	
	printf("initial -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	
	// attempt one at making as many fragments as possible w/ff
	char* ptr1[] = malloc(sizeof(char*)*(MY_HEAP_SIZE/MOD));
    
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        ptr1[i] = mymalloc_ff(MOD);
    }
    //free every other byte
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 == 0) 
        {
            myfree(ptr1[i]);
        }
    }
	printf("ff t1 -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 != 0) 
        {
            myfree(ptr1[i]);
        }
    }

	printf("freed -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());

	// attempt one at making as many fragments as possible w/bf
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        ptr1[i] = mymalloc_bf(MOD);
    }
    //free every other byte
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 == 0) 
        {
            myfree(ptr1[i]);
        }
    }
	printf("bf t1 -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 != 0) 
        {
            myfree(ptr1[i]);
        }
    }


	mmDestroy();
	
	return 0;
}
