#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include"memory_manager.h"

#define MY_HEAP_SIZE 100
#define MODULAR 2

int main()
{
	char my_heap[MY_HEAP_SIZE];
	mmInit(my_heap, MY_HEAP_SIZE);

    int MOD = MODULAR;
	
	printf("initial -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	
	char* ptr1[MY_HEAP_SIZE/MOD];

    // attempt one at making as many fragments as possible w/ff
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
	printf("t1 ff -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 != 0) 
        {
            myfree(ptr1[i]);
        }
    }


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
	printf("t1 bf -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 != 0) 
        {
            myfree(ptr1[i]);
        }
    }
    

	// attempt one at making as many fragments as possible w/wf
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        ptr1[i] = mymalloc_wf(MOD);
    }
    //free every other byte
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 == 0) 
        {
            myfree(ptr1[i]);
        }
    }
	printf("t1 wf -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 != 0) 
        {
            myfree(ptr1[i]);
        }
    }


    // attempt one at making as many fragments as possible w/ ff & bf
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        ptr1[i] = mymalloc_ff(MOD);
        if(i != 0) 
        {
            ptr1[--i] = mymalloc_bf(MOD);
        }
    }
    //free every other byte alocated
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 == 0) 
        {
            myfree(ptr1[i]);
        }
    }
	printf("t1 ff & bf -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 != 0) 
        {
            myfree(ptr1[i]);
        }
    }

    
    // attempt one at making as many fragments as possible w/ bf & ff
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        ptr1[i] = mymalloc_bf(MOD);
        if(i != 0) 
        {
            ptr1[--i] = mymalloc_ff(MOD);
        }
    }
    //free every other byte alocated
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 == 0) 
        {
            myfree(ptr1[i]);
        }
    }
	printf("t1 bf & ff -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 != 0) 
        {
            myfree(ptr1[i]);
        }
    }


    // attempt one at making as many fragments as possible w/ ff & wf
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        ptr1[i] = mymalloc_ff(MOD);
        if(i != 0) 
        {
            ptr1[--i] = mymalloc_wf(MOD);
        }
    }
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 == 0) 
        {
            myfree(ptr1[i]);
        }
    }
	printf("t1 ff & wf -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 != 0) 
        {
            myfree(ptr1[i]);
        }
    }


    // attempt one at making as many fragments as possible w/ wf & ff
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        ptr1[i] = mymalloc_wf(MOD);
        if(i != 0) 
        {
            ptr1[--i] = mymalloc_ff(MOD);
        }
    }
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 == 0) 
        {
            myfree(ptr1[i]);
        }
    }
	printf("t1 wf & ff -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 != 0) 
        {
            myfree(ptr1[i]);
        }
    }


    // attempt one at making as many fragments as possible w/ bf & wf
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        ptr1[i] = mymalloc_bf(MOD);
        if(i != 0) 
        {
            ptr1[--i] = mymalloc_wf(MOD);
        }
    }
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 == 0) 
        {
            myfree(ptr1[i]);
        }
    }
	printf("t1 bf & wf -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 != 0) 
        {
            myfree(ptr1[i]);
        }
    }


    // attempt one at making as many fragments as possible w/ wf & bf
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        ptr1[i] = mymalloc_wf(MOD);
        if(i != 0) 
        {
            ptr1[--i] = mymalloc_bf(MOD);
        }
    }
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 == 0) 
        {
            myfree(ptr1[i]);
        }
    }
	printf("t1 wf & bf -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 != 0) 
        {
            myfree(ptr1[i]);
        }
    }


    // attempt one at making as many fragments as possible w/ ff, bf, wf
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        ptr1[i] = mymalloc_ff(MOD);
        if(i != 0) 
        {
            ptr1[--i] = mymalloc_bf(MOD);
        }
        if(i != 0) 
        {
            ptr1[--i] = mymalloc_wf(MOD);
        }
    }
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 == 0) 
        {
            myfree(ptr1[i]);
        }
    }
	printf("t1 ff-bf-wf -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 != 0) 
        {
            myfree(ptr1[i]);
        }
    }


    // attempt one at making as many fragments as possible w/ ff, wf, bf
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        ptr1[i] = mymalloc_ff(MOD);
        if(i != 0) 
        {
            ptr1[--i] = mymalloc_wf(MOD);
        }
        if(i != 0) 
        {
            ptr1[--i] = mymalloc_bf(MOD);
        }
    }
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 == 0) 
        {
            myfree(ptr1[i]);
        }
    }
	printf("t1 ff-wf-bf -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 != 0) 
        {
            myfree(ptr1[i]);
        }
    }


    // attempt one at making as many fragments as possible w/ bf, ff, wf
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        ptr1[i] = mymalloc_bf(MOD);
        if(i != 0) 
        {
            ptr1[--i] = mymalloc_ff(MOD);
        }
        if(i != 0) 
        {
            ptr1[--i] = mymalloc_wf(MOD);
        }
    }
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 == 0) 
        {
            myfree(ptr1[i]);
        }
    }
	printf("t1 bf-ff-wf -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 != 0) 
        {
            myfree(ptr1[i]);
        }
    }


    // attempt one at making as many fragments as possible w/ bf, wf, ff
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        ptr1[i] = mymalloc_bf(MOD);
        if(i != 0) 
        {
            ptr1[--i] = mymalloc_wf(MOD);
        }
        if(i != 0) 
        {
            ptr1[--i] = mymalloc_ff(MOD);
        }
    }
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 == 0) 
        {
            myfree(ptr1[i]);
        }
    }
	printf("t1 bf-wf-ff -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 != 0) 
        {
            myfree(ptr1[i]);
        }
    }


    // attempt one at making as many fragments as possible w/ wf, ff, bf
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        ptr1[i] = mymalloc_wf(MOD);
        if(i != 0) 
        {
            ptr1[--i] = mymalloc_ff(MOD);
        }
        if(i != 0) 
        {
            ptr1[--i] = mymalloc_bf(MOD);
        }
    }
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 == 0) 
        {
            myfree(ptr1[i]);
        }
    }
	printf("t1 wf-ff-bf -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 != 0) 
        {
            myfree(ptr1[i]);
        }
    }


    // attempt one at making as many fragments as possible w/ wf, bf, ff
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        ptr1[i] = mymalloc_wf(MOD);
        if(i != 0) 
        {
            ptr1[--i] = mymalloc_bf(MOD);
        }
        if(i != 0) 
        {
            ptr1[--i] = mymalloc_ff(MOD);
        }
    }
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 == 0) 
        {
            myfree(ptr1[i]);
        }
    }
	printf("t1 wf-bf-ff -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 != 0) 
        {
            myfree(ptr1[i]);
        }
    }
//##########################################################################################################################################################
    //double memory size for round two of testing
    MOD = MOD*2;
    free(ptr1);

	char* ptr1[] = malloc((sizeof(char*) * (MY_HEAP_SIZE/MOD)));

    // attempt one at making as many fragments as possible w/ff
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
	printf("t2 ff -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 != 0) 
        {
            myfree(ptr1[i]);
        }
    }


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
	printf("t2 bf -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 != 0) 
        {
            myfree(ptr1[i]);
        }
    }
    

	// attempt one at making as many fragments as possible w/wf
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        ptr1[i] = mymalloc_wf(MOD);
    }
    //free every other byte
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 == 0) 
        {
            myfree(ptr1[i]);
        }
    }
	printf("t2 wf -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 != 0) 
        {
            myfree(ptr1[i]);
        }
    }


    // attempt one at making as many fragments as possible w/ ff & bf
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        ptr1[i] = mymalloc_ff(MOD);
        if(i != 0) 
        {
            ptr1[--i] = mymalloc_bf(MOD);
        }
    }
    //free every other byte alocated
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 == 0) 
        {
            myfree(ptr1[i]);
        }
    }
	printf("t2 ff & bf -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 != 0) 
        {
            myfree(ptr1[i]);
        }
    }

    
    // attempt one at making as many fragments as possible w/ bf & ff
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        ptr1[i] = mymalloc_bf(MOD);
        if(i != 0) 
        {
            ptr1[--i] = mymalloc_ff(MOD);
        }
    }
    //free every other byte alocated
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 == 0) 
        {
            myfree(ptr1[i]);
        }
    }
	printf("t2 bf & ff -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 != 0) 
        {
            myfree(ptr1[i]);
        }
    }


    // attempt one at making as many fragments as possible w/ ff & wf
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        ptr1[i] = mymalloc_ff(MOD);
        if(i != 0) 
        {
            ptr1[--i] = mymalloc_wf(MOD);
        }
    }
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 == 0) 
        {
            myfree(ptr1[i]);
        }
    }
	printf("t2 ff & wf -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 != 0) 
        {
            myfree(ptr1[i]);
        }
    }


    // attempt one at making as many fragments as possible w/ wf & ff
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        ptr1[i] = mymalloc_wf(MOD);
        if(i != 0) 
        {
            ptr1[--i] = mymalloc_ff(MOD);
        }
    }
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 == 0) 
        {
            myfree(ptr1[i]);
        }
    }
	printf("t2 wf & ff -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 != 0) 
        {
            myfree(ptr1[i]);
        }
    }


    // attempt one at making as many fragments as possible w/ bf & wf
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        ptr1[i] = mymalloc_bf(MOD);
        if(i != 0) 
        {
            ptr1[--i] = mymalloc_wf(MOD);
        }
    }
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 == 0) 
        {
            myfree(ptr1[i]);
        }
    }
	printf("t2 bf & wf -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 != 0) 
        {
            myfree(ptr1[i]);
        }
    }


    // attempt one at making as many fragments as possible w/ wf & bf
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        ptr1[i] = mymalloc_wf(MOD);
        if(i != 0) 
        {
            ptr1[--i] = mymalloc_bf(MOD);
        }
    }
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 == 0) 
        {
            myfree(ptr1[i]);
        }
    }
	printf("t2 wf & bf -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 != 0) 
        {
            myfree(ptr1[i]);
        }
    }


    // attempt one at making as many fragments as possible w/ ff, bf, wf
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        ptr1[i] = mymalloc_ff(MOD);
        if(i != 0) 
        {
            ptr1[--i] = mymalloc_bf(MOD);
        }
        if(i != 0) 
        {
            ptr1[--i] = mymalloc_wf(MOD);
        }
    }
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 == 0) 
        {
            myfree(ptr1[i]);
        }
    }
	printf("t2 ff-bf-wf -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 != 0) 
        {
            myfree(ptr1[i]);
        }
    }


    // attempt one at making as many fragments as possible w/ ff, wf, bf
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        ptr1[i] = mymalloc_ff(MOD);
        if(i != 0) 
        {
            ptr1[--i] = mymalloc_wf(MOD);
        }
        if(i != 0) 
        {
            ptr1[--i] = mymalloc_bf(MOD);
        }
    }
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 == 0) 
        {
            myfree(ptr1[i]);
        }
    }
	printf("t2 ff-wf-bf -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 != 0) 
        {
            myfree(ptr1[i]);
        }
    }


    // attempt one at making as many fragments as possible w/ bf, ff, wf
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        ptr1[i] = mymalloc_bf(MOD);
        if(i != 0) 
        {
            ptr1[--i] = mymalloc_ff(MOD);
        }
        if(i != 0) 
        {
            ptr1[--i] = mymalloc_wf(MOD);
        }
    }
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 == 0) 
        {
            myfree(ptr1[i]);
        }
    }
	printf("t2 bf-ff-wf -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 != 0) 
        {
            myfree(ptr1[i]);
        }
    }


    // attempt one at making as many fragments as possible w/ bf, wf, ff
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        ptr1[i] = mymalloc_bf(MOD);
        if(i != 0) 
        {
            ptr1[--i] = mymalloc_wf(MOD);
        }
        if(i != 0) 
        {
            ptr1[--i] = mymalloc_ff(MOD);
        }
    }
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 == 0) 
        {
            myfree(ptr1[i]);
        }
    }
	printf("t2 bf-wf-ff -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 != 0) 
        {
            myfree(ptr1[i]);
        }
    }


    // attempt one at making as many fragments as possible w/ wf, ff, bf
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        ptr1[i] = mymalloc_wf(MOD);
        if(i != 0) 
        {
            ptr1[--i] = mymalloc_ff(MOD);
        }
        if(i != 0) 
        {
            ptr1[--i] = mymalloc_bf(MOD);
        }
    }
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 == 0) 
        {
            myfree(ptr1[i]);
        }
    }
	printf("t2 wf-ff-bf -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 != 0) 
        {
            myfree(ptr1[i]);
        }
    }


    // attempt one at making as many fragments as possible w/ wf, bf, ff
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        ptr1[i] = mymalloc_wf(MOD);
        if(i != 0) 
        {
            ptr1[--i] = mymalloc_bf(MOD);
        }
        if(i != 0) 
        {
            ptr1[--i] = mymalloc_ff(MOD);
        }
    }
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 == 0) 
        {
            myfree(ptr1[i]);
        }
    }
	printf("t2 wf-bf-ff -- Available Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_fragment_count());
	//free the rest
    for(int i = (MY_HEAP_SIZE/MOD)-1; i >= 0; i--)
    {
        if(i%2 != 0) 
        {
            myfree(ptr1[i]);
        }
    }

    free(ptr1);
	mmDestroy();
	
	return 0;
}
