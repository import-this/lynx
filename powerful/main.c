/**
 * Author:	Vasilis Poulimenos
 * Date:	3/1/2015
 * Version:	1.0.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "ispowerful.h"

void usage(char *prog)
{
	fprintf(stderr, "Usage: %% %s <number>", prog);
}

int main(int argc, char *argv[])
{
	long int number;

	if (argc != 2) {
		usage(argv[0]);
		return EXIT_FAILURE;
	}

	number = strtol(argv[1], NULL, 0);
	if (errno == ERANGE) {
		fputs("The number specified is too large.", stderr);
		return EXIT_FAILURE;
	}
	if (number < 0) {
		fputs("The number specified should be positive.", stderr);
		return EXIT_FAILURE;
	}
	printf("%d\n", ispowerful((unsigned long int) number));
	return EXIT_SUCCESS;
}
