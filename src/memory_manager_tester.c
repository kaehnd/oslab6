#include "testHelper.h"
#include "memory_manager.h"
#include <stddef.h>
#include <stdlib.h>


static void *heap;

static void testInit(int size)
{
    heap = malloc(size);
    mmInit(heap, size);
}

static void testFinish()
{
    mmDestroy();
    free(heap);
}

void testFirstFit()
{
    testInit(100);

    void * first = mymalloc_ff(50);
    void * second = mymalloc_ff(20);
    void * third = mymalloc_ff(30);

    assertTrue(first != NULL && second != NULL && third != NULL);

    myfree(first);
    myfree(third);

    //should have block of 50 free, block of 20 alloc'd, and block of 30 free


    //using first fit, this will take first position
    void * smol = mymalloc_ff(30);
    assertTrue(smol != NULL);

    //this should fail, since the space 
    //of 50 free was taken by the smaller block
    void * big = mymalloc_ff(50);
    assertTrue(big == NULL);


    testFinish();
}

void testWorstFit()
{


    testInit(100);

    void * first = mymalloc_ff(50);
    void * second = mymalloc_ff(20);
    void * third = mymalloc_ff(30);

    assertTrue(first != NULL && second != NULL && third != NULL);

    myfree(first);
    myfree(third);

    //should have block of 50 free, block of 20 alloc'd, and block of 30 free


    //using first fit, this will take first position
    void * smol = mymalloc_ff(30);
    assertTrue(smol != NULL);

    //this should fail, since the space 
    //of 50 free was taken by the smaller block
    void * big = mymalloc_ff(50);
    assertTrue(big == NULL);


    testFinish();
}

void testBestFit()
{
    testInit(100);

    void * first = mymalloc_bf(50);
    void * second = mymalloc_bf(20);
    void * third = mymalloc_bf(30);

    assertTrue(first != NULL && second != NULL && third != NULL);

    myfree(first);
    myfree(third);

    //should have block of 50 free, block of 20 alloc'd, and block of 30 free


    //using best fit, this will take the spot at the end
    void * smol = mymalloc_bf(30);
    assertTrue(smol != NULL);

    //this should succeed, since the best fit placement algoritm saved 
    //the bigger chunk of memory for larger
    void * big = mymalloc_ff(50);
    assertTrue(big != NULL);


    testFinish();
}

void testMetricsFunctions()
{
}




static void single_thread_tests()
{
    startTests("memory_manager.c single-threaded");

    testFirstFit();
    testBestFit();

    finishTests();
}

int main(int argc, char * argv[])
{
    single_thread_tests();
    return 0;
}
