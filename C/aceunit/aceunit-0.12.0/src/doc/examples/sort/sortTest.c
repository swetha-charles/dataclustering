/* Copyright (c) 2007, Christian Hujer
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

/** Unit Test for sort.
 * AceUnit example for unit testing a sort function.
 * @author <a href="mailto:cher@riedquat.de">Christian Hujer</a>
 * @file sortTest.c
 */

#include <stdbool.h> // bool
#include <stddef.h> // size_t
#include <stdlib.h> // qsort
#include "sort.h"
#include "sortTest.h"


/** Comparator for int values.
 * @see comparator
 */
int compareInt(const void *o1, const void *o2) {
    const int *p1 = o1;
    const int *p2 = o2;
    return
        *p1 < *p2 ? -1 :
        *p1 > *p2 ? +1 :
        0;
}

/** Verifies that a vector is sorted.
 * @param vector  Vector to verify.
 * @param nmemb   Length of the vector to verify.
 * @param size    Size of an element within the vector.
 * @param comp    Comparator to use for the verification.
 * @return Whether the vector is sorted.
 * @retval true if the vector is sorted.
 * @retval false otherwise.
 */
bool isSorted(const void *vector, const size_t nmemb, const size_t size, const comparator comp) {
    int i;
    const char *ptr = vector;
    for (i = 0; i < nmemb - 1; i++) {
        if (comp(&ptr[i * size], &ptr[(i + 1) * size]) > 0) {
            return false;
        }
    }
    return true;
}

/** Tests that {@link compareInt()} works. */
A_Test void testCompareInt() {
    int n1;
    int n2;

    n1 = 0;
    n2 = 0;
    assertEquals("Comparing two equal numbers must return 0.", 0, compareInt(&n1, &n2));

    n1 = 1;
    n2 = 2;
    assertTrue("Comparing 1 with 2 must return a value <0.", compareInt(&n1, &n2) < 0);

    n1 = 2;
    n2 = 1;
    assertTrue("Comparing 2 with 1 must return a value >0.", compareInt(&n1, &n2) > 0);
}

/** Tests that {@link qsort()} works. */
A_Test void testSort() {
    int testling[] = { 5, 4, 3, 2, 1 };
    assertFalse("This vector is not yet sorted.", isSorted(testling, 5, sizeof(int), &compareInt));
    qsort(testling, 5, sizeof(int), &compareInt);
    assertTrue("This vector now is sorted.", isSorted(testling, 5, sizeof(int), &compareInt));
}

// Run the tests.
// Note: This is only here temporarily.
// In future versions, this part will be auto-generated.
int main(int argc, char *argv[]) {
    runFixture(&sortTestFixture);
    return 0;
}
