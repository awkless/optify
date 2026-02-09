/* SPDX-FileCopyrightText: 2026 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 */

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>

#include <optify.h>

static void
foobar(void **state)
{
	(void)state;
	assert_int_equal(3, 3);
}

int
main(void)
{
	int result = 0;
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(foobar)
	};

	result = cmocka_run_group_tests(tests, NULL, NULL);
	return result;
}
