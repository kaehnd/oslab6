# Lab 6 Report

James Rector & Danny Kaehn  
CS 3841 011  
10/24/2020  
Memory Manager  

## Introduction

This lab involved the creation of a memory manager, mimicing the `malloc` and `free` interface given by the Linux kernel. It was required to use a defined memory block allocated by a user and implement dynamic memory placement algorithms. 

## Design

We Decided that our manager was going to be similar to a Linked list. The nodes of the list contained an int value to flag if that block of memory was free or not, an int to store the size of that memory block, a void pointer as the address to that memory block, and a node pointer to the next node in the list. We then used the list to store and manage the allocated area we were given, through first fit, best fit, and worst fit management algorithms. when freeing a specific address we would first find the block set its free int to 1, then we had it merge with the previouse node if it was free, increasing previous nodes size by the freed nodes size and conecting it to the next node. Then we would combine it with the next node if it was free by increasing the new current nodes size by the next nodes value, link it to the next nodes next node, and free the next node. The algorithms were implemented with the intent as described in lab: first fit alocated at the first free node it could find, best fit went through saved the best node and alocated there, worst fit went through found the worst node and alocated the memory there.

## Build Instructions

The instructions `make` or `make all` can be used to build this solution. The command `./build/tester` will execute the general test driver, and `./build/experiment` will execute the experimental driver.

## Resources

todo

## Analysis

1. Our Experiment showed first fit and best fit at a similar quality wheras worst fit was the worst with the highest number of fragments to the lowest number of free space. Since the experiment alocated a random size for a tenth of the heap size times[heap size / 10] the exact sizes were not consistant between the methods so even if best fit would be the best the margin of error allows for a clear looser and a close race.
2. todo
3. n*(2ints + 2pointers) so about n*(24 Bytes). We could possibly combine free and size having size be negative if the node is free and positive if the node is being used but other than that i cant think of any tricks.
4. Todo

## Conclusion

todo
