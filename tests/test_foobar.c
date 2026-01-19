/* SPDX-FileCopyrightText: 2025 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 */

#include <stdarg.h>
#include <setjmp.h>
#include <stddef.h>
#include <cmocka.h>

#include <optify.h>

static void
foobar(void **state)
{
	assert_int_equal(42, 42);
}

int
main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(foobar),
	};

	int result = cmocka_run_group_tests(tests, NULL, NULL);
	return result;
}

