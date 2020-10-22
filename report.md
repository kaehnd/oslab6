# Lab 2 Report

Danny Kaehn  
CS 3841 011  
9/20/2020  
Stack Machine  

## Introduction

This lab excersize involved implementation of a stack machine in c code. It provided students an opportunity to dive back into the c language, and explore memory management when writing a program to be run on an operating system.

## Build

This program uses a makefile built using the re-usable pattern that Eclipse generates for c programs where code is placed in specific directories (.c files in ./src, .h files in ./inc). Writing the makefile in this way will allow it to be reused for any project that can follow this directory structure. Simply running "make" in the root directory of this project will compile the project.  

**Note: GNU99 extensions are used in this project**. I took the liberty of experimenting with some non-standard C functions, such as nested function declarations as well as getting the `__FUNCTION__` at a particular line of code. All needed compiler flags to support this functionality at build-time are included in the makefile.

## Design and Testing Methodology

I kept a few key design principles in mind when deciding how to implement the stack machine. First, I wanted to respect the internal structures of the stack whenever possible and use the public methods wherever possible. With the expection of `smRotate()`, all other functions not a part of the internal of the stack (internals functions being `smPop()`, `smPush()`, `smSize()`, `smClear()`, and `smTop()`) did not access any of the members of the stacm or node structures. This allows a much smoother change if the interface of the internal structure needs to change, and allows all methods to benefit any refactoring and performance improvement done in the internal methods, despite the very small performance overhead. For an implementation such as this, modularity seemed more important than performance. Also, pseudo-lambda functions were used to allow the brunt of the complex code in `smInvoke()` to be reused for all of the mathematics functions, since the only differing thing in each of the math functions is what operation to perform on the two arguments.  

However, some decisions were made specifically for the purpose of performance improvment, despite the ugly code. For example, the helper function `smInvoke()` could use `smSize()` to initially determine whether the operation can be performed and return; however, that would require iteration over the entire stack, which may be costly for a large stack and unnecessary since only the top two operands were used. To be able to access the top two items on the stack and push the result before deleting any items, the method took advantage of `smRotate()`.

To test the stack machine, I decided to write unit test-like tests for each of the functions to make the test code clean and explicit about exactly what case was being tested. To achieve this, I created a testHelper file which performs assertions of routine things like truthhood, falsehood, and equality, prints to the console the file, function, and line number of the failure and the expected and actual results upon failure, and keeps track of successes and failures. For sake of simplicity, it does not keep track of sucesses/failures by test function, but rather by assertion function call.

## Analysis

1. All of the stack machinefunctions need a “reference” to the stackstructure, and according to this design, that stackreference is passed as a pointer. Why is this necessary? Do all of the stackfunctions need this to be passed as a pointer? Any exceptions? Be specific in your answer.

    * Structs are often passed by pointer when used in function calls. For these functions in particular, this was necessary as the contents of the `stackm` struct (the `node * top` ) had to be modified by the function. If the struct was passed by value, only the copy would be modified and the original struct would be unchanged. For the `smClear()` function in particular, that would introduce a memory leak. In this implementation, only `smSize()`, `smTop()`, and `smPrint()` could be rewritten to function correctly if the stack was passed by values; however, all others would be unable to modify the top node and would leave the passed struct unchanged.

2. Unlike a Java or C++ implementation, this implementation cannot “hide” any of the internal structure of the stack. That is, users of the stackcould mess up the nextpointers if they are careless. Can you think of any way we could hide the structure of the stackto lessen the chances a user will mess up the stack? Describe in brief detail.

    * The only way we could truly hide the internals of the stack would be to keep it as a static variable in the  `stackm.c` file. This would allow users to interact with the data in the stack via the public methods, but not access the stack itself or its definition. This would hypothetically work, but would limit the use of the file to only one stack at a time (like a singleton).

3. What if all smClear() did was assign NULL to topin the stackstructure and nothing else. Would the program crash? Would there be any side effects? Try it and report results.

    * This would not cause the program to crash; however, it would never de-allocate the memory assigned to the stack or any of its nodes, resulting in process failure if the program runs long enough. Trying this myself resulted in a successful test run; however, running with valgrind revealed several memory leaks.

4. Give an example of why it might be helpful to provide an iterator or random access to elements stored in the stack (rather than always accessing the top) and outline how you could implement such a feature.

    * Providing an iterator for the structure would essentially be a matter of convenience since use of an iterator on a linked structure would just simplify the code of a while loop for traversing the structure (since foreach does not exist in c). However, implementing this as a random access structure would be very useful for functions like `smRotate()`, `smClear()` the mathematical functions, and probably even `smSize()` depending on the implementation. Implementing this would probably involve using an `int *` that is allocated with a default start size and re-allocated in chuncks as the stack grows past the defauly max number of elements(similar to Java's ArrayList class). It would likely use indexes to specify the current start and end of the stack, to prevent re-copying the entire array each time a `smPush()` or `smPop()` is called, and would probably wrap to the start of the array using modulus until reaching the start index.

## Conclusion

This lab excersize allowed me to refresh myself on c syntax and practice working with dynamic memory in c, since we had only briefly touched on `malloc()` and `free()` in embedded systems, since most i/o was built into the board and did not require dynamic sizing. I also was able to practice with the c and linux toolchain in setting up a makefile and debug configurations in VS Code.  

I found writing the `smRotate()` function very challenging, despite my efforts to diagram my implementation before starting to code. I kept getting messed up with where my node pointers would be for particular cases of the function, and having the top node needing to be changed but not of the same type of the other nodes (`stackm` vs `node`) created some confusion in my implementation. However, the unit tests for the file proved very useful in catching (hopefully) all of the bugs in the function. Secondly, I found using VIM and gdb directly to be doable, but the use of these by my unfamiliar hands was combersome and a time drain. I caved in and downloaded VS Code on my VM and found my time efficiency to skyrocket simply because of use of the familiar environment and integrated terminal, even when including the time taken to configure the task and launch configuration files.  

I liked that this lab gave us explicit permission to experiment with non-standard c capabilities, such as those in the GNU extensions. While getting used to these may make our time in a future workplace requiring strict standard compliance difficult at first, exploring the different language features has been very interesting and provides insight on the nuances of what using non-standard language features may imply (a.e. If I were to put this in git, Windows users or CI/CD runners would not be able to compile the code without use of WSL or a VM). I also liked the introduction to gdb and makefiles provided in the handout and thought they would be useful to start with and provoke curiosity to further explore their capabilities.  

This lab could potentially be improved by giving students the freedom or charge to design their own implementation of the stackm with the required public methods, allowing the professor's test driver to still be used with the code, but allowing the contents of things like the structures to be up to students. A.e. adding a size attribute to the `stackm` structure that is kept track of in `smPush()` and `smPop()`.
