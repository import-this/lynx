/**
 * Author:	Vasilis Poulimenos
 * Date:	3/1/2015
 * Version:	1.0.0
 */

/**
 * Algorithm description:
 * 1. Check if the number is divided by 2 more than once.
 *    If it is not, it is not powerful.
 * 2. Check if the number is divided by 3 more than once.
 *    If it is not, it is not powerful.
 * 3. Check if the number is divided by k or k+2 more than once (for each one
 *    of them) for all k, k+6, k+12, ... up to the square root of the number.
 *    If it is not, it is not powerful.
 *
 *    Notes:
 *    a) There is no need to check beyond the square root of the number, since:
 *           sqrt(num) * sqrt(num) = sqrt(num) ^ 2 = num
 *    b) We check in intervals of 6 because 2*3 = 6, so we have eliminated
 *       other potential prime factors already. We could increase this interval
 *       for better perfomance by checking for the next small prime factors
 *       (i.e. 5, 7, ...) early on, but this is rather pointless for the
 *       naive approach. (Use some other advanced method instead).
 * 4. If the remainder is 1 then the number specified is powerful.
 *        This approach covers the number 1 itself, which is powerful.
 *    In all other cases, the number is not powerful.
 */
int ispowerful(register unsigned long int number)
{
	unsigned long int exponent, divisor;

	if (number == 0)
		return -1;

	exponent = 0;
	while ((number & 1) == 0) {			/* number % 2 == 0 */
		number >>= 1;					/* number /= 2 */
		++exponent;
	}
	if (exponent == 1)
		return 0;

	exponent = 0;
	while (number % 3 == 0) {
		number /= 3;
		++exponent;
	}
	if (exponent == 1)
		return 0;

	for (divisor = 5; divisor * divisor <= number; divisor += 4) {
		exponent = 0;
		while (number % divisor == 0) {
			number /= divisor;
			++exponent;
		}
		if (exponent == 1)
			return 0;

		/* We add 2 here, so we add only 4 (not 6) in the next iteration. */
		divisor += 2;
		exponent = 0;
		while (number % divisor == 0) {
			number /= divisor;
			++exponent;
		}
		if (exponent == 1)
			return 0;
	}
	if (number == 1)
		return 1;
	return 0;
}
