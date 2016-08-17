/* Copyright (c) 2008, Christian Hujer
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the AceUnit developers nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef ACEUNITASSERT_H
/** Include shield to protect the header file from being included more than once. */
#define ACEUNITASSERT_H 1

#include "AceUnit.h"

/** AceUnit assertions.
 * @author <a href="mailto:cher@riedquat.de">Christian Hujer</a>
 * @file AceUnitAssert.h
 */

#ifdef ACEUNIT_EXPLICIT_MESSAGES
#include <stdio.h> /* for snprintf(). */
#endif

/** Let a test case fail.
 * @param message Message, usually with the reason why the test case failed.
 */
#define fail(message) newAssertionError(message)

/** Asserts that the specified condition is true.
 * If the condition is not true, the test case fails and raises an Assertion Error that will be logged.
 * @param message Message, usually with the positive description of why the assertion should not fail.
 * @param condition Condition to assert.
 */
#define assertTrue(message, condition) do { if (!(condition)) { fail(message); } } while (false)

/** Asserts that the specified condition is false.
 * If the condition is not false, the test case fails and raises an Assertion Error that will be logged.
 * @param message Message, usually with the positive description of why the assertion should not fail.
 * @param condition Condition to assert for false.
 */
#define assertFalse(message, condition) do { if (condition) { fail(message); } } while (false)

/** Asserts that two values are equal.
 * If the values are not equal, the test case fails and raises an Assertion Error that will be logged.
 * @note If ACEUNIT_EXPLICIT_MESSAGES is set, expected and actual are converted to int32_t.
 * @warning The underlying implementation simply compares expected and actual using !=.
 *          It is the responsibility of the user to care about the types of \p expected and \p actual.
 * @param message Message, usually with the positive description of why the assertion should not fail.
 * @param expected Expected value.
 * @param actual Actual value.
 */
#ifdef ACEUNIT_EXPLICIT_MESSAGES
#define assertEquals(message, expected, actual) \
    do { \
        int32_t lexpected = (expected); \
        int32_t lactual = (actual); \
        if (lexpected != lactual) { \
            snprintf(runnerData->explicitMsgBuf, ACEUNIT_EXPLICIT_MSG_BUF_SIZE, "%s (expected: %d, actual: %d)", message, lexpected, lactual); \
            fail(runnerData->explicitMsgBuf); \
        } \
    } while (false)
#else
#define assertEquals(message, expected, actual) do { if (!((expected) == (actual))) { fail(message); } } while (false)
#endif

/** Asserts that two values are not equal.
 * If the values are equal, the test case fails and raises an {@link AssertionError_t} that will be logged.
 * @note If ACEUNIT_EXPLICIT_MESSAGES is set, expected and actual are converted to int32_t.
 * @warning The underlying implementation simply compares expected and actual using ==.
 *          It is the responsibility of the user to care about the types of \p expected and \p actual.
 * @param message Message, usually with the positive description of why the assertion should not fail.
 * @param unexpected Not expected value.
 * @param actual Actual value.
 */
#ifdef ACEUNIT_EXPLICIT_MESSAGES
#define assertNotEquals(message, unexpected, actual) \
    do { \
        int32_t lunexpected = unexpected; \
        int32_t lactual = actual; \
        if (lunexpected == lactual) { \
            snprintf(runnerData->explicitMsgBuf, ACEUNIT_EXPLICIT_MSG_BUF_SIZE, "%s (unexpected: %d, actual: %d)", message, lunexpected, lactual); \
            fail(runnerData->explicitMsgBuf); \
        } \
    } while (false)
#else
#define assertNotEquals(message, unexpected, actual) do { if ((unexpected) == (actual)) { fail(message); } } while (false)
#endif

/** Asserts that a pointer is not NULL.
 * If the pointer is NULL, the test case fails and raises an {@link AssertionError_t} that will be logged.
 * @param message Message, usually with the positive description of why the assertion should not fail.
 * @param ptr Pointer expected to be not NULL.
 */
#define assertNotNull(message, ptr) do { if (NULL == (ptr)) { fail(message); } } while (false)

/** Asserts that a pointer is NULL.
 * If the pointer is not NULL, the test case fails and raises an {@link AssertionError_t} that will be logged.
 * @param message Message, usually with the positive description of why the assertion should not fail.
 * @param ptr Pointer expected to be NULL.
 */
#define assertNull(message, ptr) do { if (NULL != (ptr)) { fail(message); } } while (false)

#endif /* ACEUNITASSERT_H */
