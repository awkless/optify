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
catch_null_parser_state(void **state)
{
	(void)state;
	struct optify pstate = {0};
	char *argv[] = { "hello", NULL };
	int result = 0;

	result = optify_init(NULL, NULL, 0);
	assert_int_equal(result, -OPTIFY_BAD_API_USE);

	result = optify_init(&pstate, NULL, 0);
	assert_int_equal(result, -OPTIFY_BAD_API_USE);

	result = optify_init(NULL, argv, 1);
	assert_int_equal(result, -OPTIFY_BAD_API_USE);

	result = optify_init(&pstate, argv, 1);
	assert_int_equal(result, OPTIFY_SUCCESS);
}

int
main(void)
{
	int result = 0;
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(catch_null_parser_state)
	};

	result = cmocka_run_group_tests(tests, NULL, NULL);
	return result;
}
