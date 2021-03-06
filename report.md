# Lab 6 Report

James Rector & Danny Kaehn  
CS 3841 011  
10/24/2020  
Memory Manager  

## Introduction

This lab involved the creation of a memory manager, mimicing the `malloc` and `free` interface given by the Linux kernel. It was required to use a defined memory block allocated by a user and implement dynamic memory placement algorithms. The memory manager was also required to be thread-safe. Thus, this lab was intended to reinforce students' comprehension of concurrency, and to gain experiental knowledge of the different dynamic memory placement algorithms discussed in class.

## Design

We Decided that our manager was going to be similar to a Linked list. The nodes of the list contained an int value to flag if that block of memory was free or not, an int to store the size of that memory block, a void pointer as the address to that memory block, and a node pointer to the next node in the list. We then used the list to store and manage the allocated area we were given, through first fit, best fit, and worst fit management algorithms. when freeing a specific address we would first find the block set its free int to 1, then we had it merge with the previouse node if it was free, increasing previous nodes size by the freed nodes size and conecting it to the next node. Then we would combine it with the next node if it was free by increasing the new current nodes size by the next nodes value, link it to the next nodes next node, and free the next node. The algorithms were implemented with the intent as described in lab: first fit alocated at the first free node it could find, best fit went through saved the best node and alocated there, worst fit went through found the worst node and alocated the memory there.

## Build Instructions

The instructions `make` or `make all` can be used to build this solution. The command `./build/tester` will execute the general test driver, and `./build/experiment` will execute the experimental driver.

## Resources

We did not use any exernal resources for this lab, except for using test helper files created during previous labs to make testing using asserts easier and possible.

## Analysis

1. Our Experiment showed first fit and best fit at a similar quality (ff 2315 available 169 fragments 1223 allcos, bf 1411 available 110 fragments 1861 allocs) wheras worst fit was the worst with the highest number of fragments to the lowest number of free space. Since the experiment alocated a random size for a tenth of the heap size times[heap size / 10] the exact sizes were not consistant between the methods so even if best fit would be the best the margin of error allows for a clear looser and a close race.
2. Technically, the time complexity of each of the mymalloc functions is O(n) (where n is the size of the memory block provided), since even the first fit might have to loop through all of memory on the rainy-day case that all of memory is full. Based on the expectation that the calls for operating systems should be O(1), this does not meet that expectation. This could be circumvented by keeping track of free and allocated blocks of memory in separate linked lists, sorted by size available. Then, search algorithms with time complexity such as O(log(n)) could be used to find the first, best, and worst-fitting blocks. Freeing memory and coalescing blocks would be slower in this case, as more complicated loops and math would be needed to figure out what nodes are adjacent in memory. This could be solved by duplicate data structures, where the top level nodes of the free and allocated sorted doubly linked lists each pointed to a node of the linkedlist in memory sorted order.
3. n*(2ints + 2pointers) so about n*(24 Bytes). We could possibly combine free and size having size be negative if the node is free and positive if the node is being used but other than that i cant think of any tricks.
4. Detecting memory leaks reliably would be very difficult in the C language, as implied by the fact that the Linux kernel doesn't actually implement this. This is mostly due to the static nature of compiled C; it cannot use things like reflection used in higher level languages running in an intermediate form. As a result, the only way to catch leaks from the perspective of our program might simply be freeing blocks that have been allocated for x amount of time. This may be VERY dangerous, as it may result in accidentally de-allocating memory that the user was still using, causing their program to crash. This may be manageable; however, by setting the timeout on memory to multiple days, long enough to _hopefully_ avoid destroying user memory but short enough to make a difference on a program's total memory footprint over an extended period of time. Implementing this would simply involve taking the time when a block is allocated, and if it is still allocated after the decided amount of time, simply freeing that block of memory.

## Conclusion

One of the more difficult things in this lab was finding good ways to write tests that verified the functionality of each of the memory placement algorithms. Since the data structure used by the memory manager was completely internal (and mocks don't exist in C), verifying the position of placed blocks of memory had to be done by verifying whether certain test allocations would fail or not, which was most likely accurate, but was technically error-prone. Also, handling all of the edge cases for the different publicly exposed methods elegantly was somewhat challenging; I found several bugs during testing that were caused by `>=` vs `>` misapropriation. I liked that we were allowed to design our own data structure for the lab and not given requirements for it, and would have enjoyed being a bit more adventurous with the structure if time was not as much of a constraint.  This might be able to be improved for others by encouraging us to comply to a certain time complexity from the start of the lab (though this may make the lab fairly more challenging).
