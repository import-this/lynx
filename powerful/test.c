/**
 * Author:	Vasilis Poulimenos
 * Date:	3/1/2015
 * Version:	1.0.0
 */

#include <stdio.h>
#include <stdlib.h>

#include "ispowerful.h"

void assertTrue(int condition, unsigned long int number)
{
	if (!condition) {
		fprintf(stderr, "Should be true: %ld\n", number);
		exit(EXIT_FAILURE);
	}
}

void assertFalse(int condition, unsigned long int number)
{
	if (condition) {
		fprintf(stderr, "Should be false: %ld\n", number);
		exit(EXIT_FAILURE);
	}
}

void assertError(int condition, unsigned long int number)
{
	if (condition != -1) {
		fprintf(stderr, "Should raise error: %ld\n", number);
		exit(EXIT_FAILURE);
	}
}

int main(void)
{
	unsigned long int powerful[] = {
		/* http://oeis.org/A001694 */
		1, 4, 8, 9, 16, 25, 27, 32, 36, 49, 64, 72, 81, 100, 108, 121, 125, 128,
		144, 169, 196, 200, 216, 225, 243, 256, 288, 289, 324, 343, 361, 392,
		400, 432, 441, 484, 500, 512, 529, 576, 625, 648, 675, 676, 729, 784,
		800, 841, 864, 900, 961, 968, 972, 1000,
		/* Some random numbers that are powerful */
		32, 841, 961, 972, 1024, 1521, 2312, 2744, 2916, 3087, 4900, 5408, 8000,
		10976, 13068, 13824, 15876, 17956, 18000, 19600, 19881, 21600, 25088,
		26244, 27556, 30375,
		/* Some numbers that are powerful by construction */
		2*2, 3*3, 5*5, 7*7, 101*101,
		2*2 * 3*3 * 5*5,
		2*2 * 3*3 * 5*5 * 7*7,
		2*2*2, 3*3*3, 5*5*5, 7*7*7, 101*101*101,
		2*2*2 * 3*3 * 7*7,
		2*2*2 * 3*3 * 7*7 * 11*11,
		2*2*2*2*2,
		3*3*3*3*3,
		5*5*5*5*5,
		11*11, 13*13, 17*17,
		3*3 * 7*7 * 13*13,
		227*227, 229*229
	};

	unsigned long int notpowerful[] = {
		/* Primes - http://oeis.org/A000040 */
		2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67,
		71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139,
		149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223,
		227, 229, 233, 239, 241, 251, 257, 263, 269, 271,
		/* Some random numbers that are not powerful */
		279,
		/* Some numbers that are not powerful by construction */
		2 * 3 * 5 * 7 * 11,
		2 * 3 * 5 * 7 * 11*11,
		2*2*2 * 3*3 * 7 * 11*11,
		2*2*2 * 3*3 * 7*7 * 11,
		3*3 * 7*7 * 13*13 * 19,
		43*43 * 47 * 83*83,
		229*229 * 233
	};

	const unsigned long int invalid = 0;

	int i, size;

	size = sizeof powerful / sizeof *powerful;
	for (i = 0; i < size; ++i) {
		assertTrue(ispowerful(powerful[i]), powerful[i]);
	}

	size = sizeof notpowerful / sizeof *notpowerful;
	for (i = 0; i < size; ++i) {
		assertFalse(ispowerful(notpowerful[i]), notpowerful[i]);
	}

	assertError(ispowerful(invalid), invalid);

	puts("TESTS PASSED");
	return EXIT_SUCCESS;
}
