/* 
 * memory_manager_tester.c
 *
 * James Rector and Daniel Kaehn
 * CS 3841 Lab 6: Memory Manager
 * 10/25/2020
 */

#include "testHelper.h"
#include "memory_manager.h"
#include <stddef.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>

static void *heap;

static int segfaultEncountered;
static int threadStart;


void signalHandler(int sig)
{
    if (sig == SIGSEGV){
        segfaultEncountered = 1;
    }
}


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



static void testFirstFit()
{
    testInit(100);

    void *first = mymalloc_ff(50);
    void *second = mymalloc_ff(20);
    void *third = mymalloc_ff(30);

    assertTrue(first != NULL && second != NULL && third != NULL);

    myfree(first);
    myfree(third);

    //should have block of 50 free, block of 20 alloc'd, and block of 30 free

    //using first fit, this will take first position
    void *smol = mymalloc_ff(30);
    assertTrue(smol != NULL);

    //this should fail, since the space
    //of 50 free was decreased to 20 by smaller block
    void *big = mymalloc_ff(50);
    assertTrue(big == NULL);

    testFinish();
}

void testWorstFit()
{

    testInit(100);

    void *first = mymalloc_wf(30);
    void *second = mymalloc_wf(20);
    void *third = mymalloc_wf(50);

    assertTrue(first != NULL && second != NULL && third != NULL);

    myfree(first);
    myfree(third);

    //should have block of 30 free, block of 20 alloc'd, and block of 50 free

    //using worst fit, this will take last position
    void *smol = mymalloc_wf(10);
    assertTrue(smol != NULL);

    //this should fail, since the space
    //of 50 free was decreased to 40 by smaller block
    void *big = mymalloc_wf(50);
    assertTrue(big == NULL);

    testFinish();
}

static void testBestFit()
{
    testInit(100);

    void *first = mymalloc_bf(50);
    void *second = mymalloc_bf(20);
    void *third = mymalloc_bf(30);

    assertTrue(first != NULL && second != NULL && third != NULL);

    myfree(first);
    myfree(third);

    //should have block of 50 free, block of 20 alloc'd, and block of 30 free

    //using best fit, this will take the spot at the end
    void *smol = mymalloc_bf(30);
    assertTrue(smol != NULL);

    //this should succeed, since the best fit placement algoritm saved
    //the bigger chunk of memory for larger
    void *big = mymalloc_ff(50);
    assertTrue(big != NULL);

    testFinish();
}


static void testMetricsFunctions()
{

    testInit(100);

    assertEqual(0, get_allocated_space());
    assertEqual(100, get_remaining_space());
    assertEqual(1, get_fragment_count());
    assertEqual(0, get_mymalloc_count());

    void *first = mymalloc_bf(50);

    assertEqual(50, get_allocated_space());
    assertEqual(50, get_remaining_space());
    assertEqual(1, get_fragment_count());
    assertEqual(1, get_mymalloc_count());

    void *second = mymalloc_bf(20);

    assertEqual(70, get_allocated_space());
    assertEqual(30, get_remaining_space());
    assertEqual(1, get_fragment_count());
    assertEqual(2, get_mymalloc_count());

    void *third = mymalloc_bf(30);

    assertEqual(100, get_allocated_space());
    assertEqual(0, get_remaining_space());
    assertEqual(0, get_fragment_count());
    assertEqual(3, get_mymalloc_count());

    assertTrue(first != NULL && second != NULL && third != NULL);

    testFinish();
}


static void testFree()
{

    testInit(100);

    void * thing1 = mymalloc_bf(60);
    void * thing2 = mymalloc_bf(20);

    myfree(thing1);

    assertEqual(20, get_allocated_space());
    assertEqual(80, get_remaining_space());
    assertEqual(2, get_fragment_count());
    assertEqual(2, get_mymalloc_count());

    //ensure that free coalesces adjacent blocks
    myfree(thing2);
    assertEqual(1, get_fragment_count());

    //ensure duplicate free causes a segfault
    signal(SIGSEGV, signalHandler);

    segfaultEncountered = 0;
    myfree(thing1);
    assertTrue(segfaultEncountered);

    signal(SIGSEGV, SIG_DFL);

    testFinish();
}

static void testBigMemory()
{
    testInit(100000);

    void ** locations = malloc(100 * sizeof(void *));


    for (int i = 0; i < 100; i++)
    {
        locations[i] = mymalloc_ff(1000);
        assertEqual(i+1, get_mymalloc_count());
    }

    assertEqual(0, get_remaining_space());

    for (int i = 0; i < 100; i++)
    {
        myfree(locations[i]);
    }

    assertEqual(100000, get_remaining_space());

    free(locations);

    testFinish();
}


static void * threadsPassing()
{
    while (!threadStart);

    void ** locations = malloc(10 * sizeof(void *));

    for (int i = 0; i < 10; i++)
    {
        locations[i] = mymalloc_ff(1);
        assertTrue(locations[i] != NULL);
    }

    for (int i = 0; i < 10; i++)
    {
        myfree(locations[i]);
    }

    free(locations);

    return NULL;
}

static void testMultithreaded()
{
    testInit(1000);

    pthread_t threads[100];

    for (int i = 0; i < 100; i++){
        pthread_create(&threads[i],NULL,threadsPassing, NULL);
    }

    threadStart = 1;

    for (int i = 0; i < 100; i++)
    {
        pthread_join(threads[i], NULL);
    }

    assertEqual(1000, get_remaining_space());
    assertEqual(1000, get_mymalloc_count());

    testFinish();
}

int main()
{
    startTests("memory_manager.c");

    testFirstFit();
    testBestFit();
    testWorstFit();
    
    testMetricsFunctions();
    testFree();

    testBigMemory();

    testMultithreaded();

    finishTests();
}
