/* SPDX-FileCopyrightText: 2026 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 */

#include <stdio.h>

#include "sort.h"

int
main(void) {
	int array[10] = {12, 8, 13, 4, 0, 1, 33, 8, 9, 2};
	insertion_sort(array, 10);
	printf("[");
	for (int i = 0; i < 10; ++i) {
		if (i == 9)
			printf("%d", array[i]);
		else
			printf("%d, ", array[i]);
	}
	printf("]\n");

	return 0;
}
