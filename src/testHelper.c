/**
 * Danny Kaehn
 * CS 3841-011
 * Lab 2: Stack Machine
 * 
 * testHelper.c: some useful methods for creating assertions
 *  with helpful error messages pointing to the source
 */


#include <stdlib.h>
#include <stdio.h>
#include "testHelper.h"

static const char red[] = "\x1b[31m";
static const char green[] = "\x1b[32m";
static const char clrRst[] = "\x1b[0m";

static int failedAssertions = 0;
static int passedAssertions = 0;
static char * currentTestName;

/*
 * Initialize test session and print start message
 */
void startTests(char * testName) 
{
    currentTestName = testName;
    printf("*********************************************"
        "\nStarting Tests for %s...\n"
        "*********************************************\n\n",
        testName);
}

/*
 * End a test session and print results  
 */
void finishTests()
{
        printf("\n\n*********************************************"
        "\nEnd Tests for %s...\n"
        "%s%d assertions passed%s\n"
        "%s%d assertions failed %s\n"
        "*********************************************\n\n",
        currentTestName, green, passedAssertions, clrRst,
        failedAssertions ? red : green, failedAssertions, clrRst);
}

/*
 * Asserts that the provided condition is true
 */
void _meta_assertTrue(const char * file, const char * function, int lineNum, int condition)
{
    if(condition)
    {
        _meta_assertTestPass();
    } 
    else 
    {
        _meta_assertTestFail(file, function, lineNum, "True", "False");
    }
}

/*
 * Asserts that the provided condition is false
 */
void _meta_assertFalse(const char * file, const char * function, int lineNum, int condition)
{
    if(condition)
    {
        _meta_assertTestFail(file, function, lineNum, "False", "True");
    } 
    else
    {
        _meta_assertTestPass();
    }
}

/*
 * Asserts that the provided integers are equal
 */
void _meta_assertEqual(const char * file, const char * function, int lineNum, int a, int b)
{
    if (a == b)
    {
        _meta_assertTestPass();
    }
    else 
    {
        char * expected = malloc(snprintf(NULL, 0, "%d", a)+1);
        char * actual = malloc(snprintf(NULL, 0, "%d", b)+1);
        sprintf(expected, "%d", a);
        sprintf(actual, "%d", b);

        _meta_assertTestFail(file, function, lineNum, expected, actual);
    }
}

/*
 * Prints a failure message based on an expected condition that was not met
 * Counts the failure internally
 */
void _meta_assertTestFail(const char * file, const char * function, int lineNum, char * expected, char * actual)
{
    printf("%sTEST FAIL\n\n"
    "..in file %s\n\n"
    "..in function %s\n\n" 
    "..at line %d\n\n"
    "Expected: %s\tActual: %s%s\n\n\n",
    red, file, function, lineNum, expected, actual, clrRst);
    failedAssertions++;
}

/*
 * Counts a test pass internally
 */
void _meta_assertTestPass()
{
    passedAssertions++;
}
