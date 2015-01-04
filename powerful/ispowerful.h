/**
 * A small module for testing powerfulness of numbers.
 *
 * References on powerful numbers:
 *     http://en.wikipedia.org/wiki/Powerful_number
 *     http://oeis.org/A001694
 *     http://mathworld.wolfram.com/PowerfulNumber.html
 *
 * Author:	Vasilis Poulimenos
 * Date:	3/1/2015
 * Version:	1.0.0
 */

#ifndef ISPOWERFUL_H_
#define ISPOWERFUL_H_

/**
 * Checks if the number specified is powerful.
 *
 * This function uses a naive algorithm based on trivial division to test
 * for powerfulness. As a result, it will be slow for very large numbers.
 *
 * Returns 1 if the number is powerful or 0 otherwise.
 * Raises an error (by returning -1) in case of invalid input (i.e. 0 (zero)).
 */
int ispowerful(unsigned long int);

#endif /* ISPOWERFUL_H_ */
