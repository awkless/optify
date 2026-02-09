/* SPDX-FileCopyrightText: 2026 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 */

#ifndef SORT_H
#define SORT_H

#include <stddef.h>

/**
 * @brief Basic insertion sort implementation.
 *
 * Will sort input array in-place.
 *
 * @precondition `array` cannot be NULL.
 * @precondition `len` cannot be zero.
 *
 * @param[in,out] array The input array to be sorted.
 * @param[in] len The length of the input array.
 */
void
insertion_sort(int *array, size_t len);

#endif /* SORT_H */
