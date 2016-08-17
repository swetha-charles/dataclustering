/** AceUnit test header file for fixture test.
 *
 * You may wonder why this is a header file and yet generates program elements.
 * This allows you to declare test methods as static.
 *
 * @warning This is a generated file. Do not edit. Your changes will be lost.
 * @file test.h
 */

#ifndef _TEST_H
/** Include shield to protect this header file from being included more than once. */
#define _TEST_H

/** The id of this fixture. */
#define A_FIXTURE_ID 1

#include "AceUnit.h"

/* The prototypes are here to be able to include this header file at the beginning of the test file instead of at the end. */
A_Test void someMethodImplementation(void);

/** The test case ids of this fixture. */
static const TestCaseId_t testIds[] = {
    2, /* someMethodImplementation */
};

#ifndef ACEUNIT_EMBEDDED
/** The test names of this fixture. */
static const char *const testNames[] = {
    "someMethodImplementation",
};
#endif

#ifdef ACEUNIT_LOOP
/** The loops of this fixture. */
static const aceunit_loop_t loops[] = {
    1,
};
#endif

#ifdef ACEUNIT_GROUP
/** The groups of this fixture. */
static const AceGroupId_t groups[] = {
    0,
};
#endif

/** The test cases of this fixture. */
static const testMethod_t testCases[] = {
    someMethodImplementation,
    NULL
};

/** The before methods of this fixture. */
static const testMethod_t before[] = {
    NULL
};

/** The after methods of this fixture. */
static const testMethod_t after[] = {
    NULL
};

/** The beforeClass methods of this fixture. */
static const testMethod_t beforeClass[] = {
    NULL
};

/** The afterClass methods of this fixture. */
static const testMethod_t afterClass[] = {
    NULL
};

/** This fixture. */
#if defined __cplusplus
extern
#endif
const TestFixture_t testFixture = {
    1,
#ifndef ACEUNIT_EMBEDDED
    "test",
#endif
#ifdef ACEUNIT_SUITES
    NULL,
#endif
    testIds,
#ifndef ACEUNIT_EMBEDDED
    testNames,
#endif
#ifdef ACEUNIT_LOOP
    loops,
#endif
#ifdef ACEUNIT_GROUP
    groups,
#endif
    testCases,
    before,
    after,
    beforeClass,
    afterClass
};

#endif /* _TEST_H */
