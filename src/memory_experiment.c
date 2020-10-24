#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include"memory_manager.h"

#define MY_HEAP_SIZE 10000
#define DEV 10
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

/*
    // attempt one at making as many fragments as possible w/ ff & bf
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        ptr[i] = mymalloc_ff(MOD);
        if(i != 0) 
        {
            ptr[--i] = mymalloc_bf(MOD);
        }
    }
    //free every other byte
    free_alternating_bytes(ptr1, MOD);
    
	printf("t1 ff & bf -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    free_all_bytes(ptr1, MOD);

    
    // attempt one at making as many fragments as possible w/ bf & ff
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        ptr[i] = mymalloc_bf(MOD);
        if(i != 0) 
        {
            ptr[--i] = mymalloc_ff(MOD);
        }
    }
    //free every other allocation
    free_alternating_bytes(ptr1, MOD);
    
	printf("t1 bf & ff -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    free_all_bytes(ptr1, MOD);


    // attempt one at making as many fragments as possible w/ ff & wf
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        ptr[i] = mymalloc_ff(MOD);
        if(i != 0) 
        {
            ptr[--i] = mymalloc_wf(MOD);
        }
    }
    //free every other allocation
    free_alternating_bytes(ptr1, MOD);
    
	printf("t1 ff & wf -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    free_all_bytes(ptr1, MOD);


    // attempt one at making as many fragments as possible w/ wf & ff
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        ptr[i] = mymalloc_wf(MOD);
        if(i != 0) 
        {
            ptr[--i] = mymalloc_ff(MOD);
        }
    }
    //free every other allocation
    free_alternating_bytes(ptr1, MOD);
    
	printf("t1 wf & ff -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    free_all_bytes(ptr1, MOD);


    // attempt one at making as many fragments as possible w/ bf & wf
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        ptr[i] = mymalloc_bf(MOD);
        if(i != 0) 
        {
            ptr[--i] = mymalloc_wf(MOD);
        }
    }
    //free every other allocation
    free_alternating_bytes(ptr1, MOD);
    
	printf("t1 bf & wf -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    free_all_bytes(ptr1, MOD);


    // attempt one at making as many fragments as possible w/ wf & bf
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        ptr[i] = mymalloc_wf(MOD);
        if(i != 0) 
        {
            ptr[--i] = mymalloc_bf(MOD);
        }
    }
    //free every other allocation
    free_alternating_bytes(ptr1, MOD);
    
	printf("t1 wf & bf -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    free_all_bytes(ptr1, MOD);


    // attempt one at making as many fragments as possible w/ ff, bf, wf
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        ptr[i] = mymalloc_ff(MOD);
        if(i != 0) 
        {
            ptr[--i] = mymalloc_bf(MOD);
        }
        if(i != 0) 
        {
            ptr[--i] = mymalloc_wf(MOD);
        }
    }
    //free every other allocation
    free_alternating_bytes(ptr1, MOD);
    
	printf("t1 ff-bf-wf -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    free_all_bytes(ptr1, MOD);


    // attempt one at making as many fragments as possible w/ ff, wf, bf
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        ptr[i] = mymalloc_ff(MOD);
        if(i != 0) 
        {
            ptr[--i] = mymalloc_wf(MOD);
        }
        if(i != 0) 
        {
            ptr[--i] = mymalloc_bf(MOD);
        }
    }
    //free every other allocation
    free_alternating_bytes(ptr1, MOD);
    
	printf("t1 ff-wf-bf -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    free_all_bytes(ptr1, MOD);


    // attempt one at making as many fragments as possible w/ bf, ff, wf
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        ptr[i] = mymalloc_bf(MOD);
        if(i != 0) 
        {
            ptr[--i] = mymalloc_ff(MOD);
        }
        if(i != 0) 
        {
            ptr[--i] = mymalloc_wf(MOD);
        }
    }
    //free every other allocation
    free_alternating_bytes(ptr1, MOD);
    
	printf("t1 bf-ff-wf -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    free_all_bytes(ptr1, MOD);


    // attempt one at making as many fragments as possible w/ bf, wf, ff
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        ptr[i] = mymalloc_bf(MOD);
        if(i != 0) 
        {
            ptr[--i] = mymalloc_wf(MOD);
        }
        if(i != 0) 
        {
            ptr[--i] = mymalloc_ff(MOD);
        }
    }
    //free every other allocation
    free_alternating_bytes(ptr1, MOD);
    
	printf("t1 bf-wf-ff -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    free_all_bytes(ptr1, MOD);


    // attempt one at making as many fragments as possible w/ wf, ff, bf
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        ptr[i] = mymalloc_wf(MOD);
        if(i != 0) 
        {
            ptr[--i] = mymalloc_ff(MOD);
        }
        if(i != 0) 
        {
            ptr[--i] = mymalloc_bf(MOD);
        }
    }
    //free every other allocation
    free_alternating_bytes(ptr1, MOD);
    
	printf("t1 wf-ff-bf -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    free_all_bytes(ptr1, MOD);


    // attempt one at making as many fragments as possible w/ wf, bf, ff
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        ptr[i] = mymalloc_wf(MOD);
        if(i != 0) 
        {
            ptr[--i] = mymalloc_bf(MOD);
        }
        if(i != 0) 
        {
            ptr[--i] = mymalloc_ff(MOD);
        }
    }
    //free every other allocation
    free_alternating_bytes(ptr1, MOD);
    
	printf("t1 wf-bf-ff -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    free_all_bytes(ptr1, MOD);
*/
    free(ptr);
	mmDestroy();
	
	return 0;
}
