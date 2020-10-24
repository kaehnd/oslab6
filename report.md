# Lab 6 Report

James Rector & Danny Kaehn  
CS 3841 011  
10/24/2020  
Memory Manager  

## Introduction

This lab involved the creation of a memory manager, mimicing the `malloc` and `free` interface given by the Linux kernel. It was required to use a defined memory block allocated by a user and implement dynamic memory placement algorithms.

## Design

todo

## Build Instructions

The instructions `make` or `make all` can be used to build this solution. The command `./build/tester` will execute the general test driver, and `./build/experiment` will execute the experimental driver.

## Resources

We did not use any exernal resources for this lab, except for using test helper files created during previous labs to make testing using asserts easier and possible.

## Analysis

1. todo James
2. Technically, the time complexity of each of the mymalloc functions is O(n) (where n is the size of the memory block provided), since even the first fit might have to loop through all of memory on the rainy-day case that all of memory is full. Based on the expectation that the calls for operating systems should be O(1), this does not meet that expectation. This could be circumvented by keeping track of free and allocated blocks of memory in separate linked lists, sorted by size available. Then, search algorithms with time complexity such as O(log(n)) could be used to find the first, best, and worst-fitting blocks. Freeing memory and coalescing blocks would be slower in this case, as more complicated loops and math would be needed to figure out what nodes are adjacent in memory. This could be solved by duplicate data structures, where the top level nodes of the free and allocated sorted doubly linked lists each pointed to a node of the linkedlist in memory sorted order.
3. Todo
4. Todo

## Conclusion

todo
