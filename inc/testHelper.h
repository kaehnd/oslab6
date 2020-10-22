/**
 * Danny Kaehn
 * CS 3841-011
 * Lab 2: Stack Machine
 * 
 * testHelper.h: declarations of some useful methods for creating assertions
 * with helpful error messages pointing to the source; uses macros to
 * add file, function, and line number of of source call
 * 
 ***Can only have one test session active at a time
 * (done to prevent passing a test session struct around all the time)
 */

#ifndef TESTHELPER
#define TESTHELPER

//quality of life macros to avoid calling functions with calling metadata each time

#define assertTrue(condition) _meta_assertTrue(__FILE__, __FUNCTION__, __LINE__, condition)
#define assertFalse(condition) _meta_assertFalse(__FILE__, __FUNCTION__, __LINE__, condition)
#define assertEqual(a, b) _meta_assertEqual(__FILE__, __FUNCTION__, __LINE__, a, b)
#define assertTestFail(expected, actual) _meta_assertTestFail(__FILE__, __FUNCTION__, __LINE__, expected, actual)
#define assertTestPass() _meta_assertTestPass()

/*
 * Initialize test session and print start message
 */
void startTests(char * testName);

/*
 * End a test session and print results  
 */
void finishTests();

/*
 * Asserts that the provided condition is true
 */
void _meta_assertTrue(const char * file, const char * function, int lineNum, int condition);

/*
 * Asserts that the provided condition is false
 */
void _meta_assertFalse(const char * file, const char * function, int lineNum, int condition);

/*
 * Asserts that the provided integers are equal
 */
void _meta_assertEqual(const char * file, const char * function, int lineNum, int a, int b);

/*
 * Prints a failure message based on an expected condition that was not met
 * Counts the failure internally
 */
void _meta_assertTestFail(const char * file, const char * function, int lineNum, char * expected, char * actual);

/*
 * Counts a test pass internally
 */
void _meta_assertTestPass();

#endif
