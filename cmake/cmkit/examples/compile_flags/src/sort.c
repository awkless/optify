/* SPDX-FileCopyrightText: 2026 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 */

#include "sort.h"

void
insertion_sort(int *array, size_t len)
{
	if (!array || len == 0)
		return;

	for (size_t i = 0; i < len; ++i) {
		int key = array[i];
		int j = i - 1;
		while (array[j] > key && i > 0) {
			array[j + 1] = array[j];
			--j;
		}
		array[j + 1] = key;
	}
}
