/* SPDX-FileCopyrightText: 2026 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 */

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <cmocka.h>

#include <optify.h>

/*
 * Test that `optify_init` catches invalid parameters.
 *
 * Make sure that `optify_init` catches the following:
 *   - Parameter `self` is NULL.
 *   - Parameter `argv` is NULL.
 */
static void
catch_invalid_parameters(void **state)
{
	(void)state;
	struct optify argp = { 0 };
	char *argv[] = { "hello", NULL };
	int argc = 1;
	int result = 0;

	result = optify_init(NULL, NULL, 0);
	assert_int_equal(result, -OPTIFY_ERR_INVALID_PARAM);

	result = optify_init(&argp, NULL, 0);
	assert_int_equal(result, -OPTIFY_ERR_INVALID_PARAM);

	result = optify_init(NULL, argv, argc);
	assert_int_equal(result, -OPTIFY_ERR_INVALID_PARAM);

	result = optify_init(&argp, argv, argc);
	assert_int_equal(result, OPTIFY_OK);
}

int
main(void)
{
	int result = 0;
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(catch_invalid_parameters)
	};

	result = cmocka_run_group_tests(tests, NULL, NULL);
	return result;
}
