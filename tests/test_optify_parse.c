/* SPDX-FileCopyrightText: 2026 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 */

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <cmocka.h>

#include <optify.h>

#define OPTCNT 3
static const struct optify_option optlist[] = {
	{ .shortid = 'v', .longid = "verbosity", .argkind = OPTIFY_OPTIONAL_ARG },
	{ .shortid = 'c', .longid = "color", .argkind = OPTIFY_REQUIRED_ARG },
	{ .shortid = 'h', .longid = "help", .argkind = OPTIFY_NO_ARG },
	OPTIFY_OPTLIST_END
};

static void
catch_bad_parameters(void **state)
{
	(void)state;
	struct optify argp = {0};
	char *argv[] = { "test", NULL };
	int argc = 1;
	int result = 0;

	result = optify_init(&argp, argv, argc);
	if (result != OPTIFY_OK)
		fail_msg("State initialization failed for some reason");

	result = optify_parse(NULL, NULL, 0);
	assert_int_equal(result, -OPTIFY_ERR_INVALID_PARAM);

	result = optify_parse(&argp, NULL, 0);
	assert_int_equal(result, -OPTIFY_ERR_INVALID_PARAM);

	result = optify_parse(NULL, optlist, OPTCNT);
	assert_int_equal(result, -OPTIFY_ERR_INVALID_PARAM);

	result = optify_parse(&argp, optlist, OPTCNT);
	assert_int_equal(result, OPTIFY_PARSE_END);
}

/*
 * Test that `optify_parse` can catch unknown short options.
 *
 * Parser must detect options that do not exist in option entry list. A few
 * positionals are thrown in the mix to ensure that the parser does break
 * when encountering them.
 */
static void
catch_unknown_short_option(void **state)
{
	(void)state;
	struct optify argp = {0};
	char *argv[] = { "test", "foo", "-x", "-h", "bar", "-y", NULL };
	int argc = 6;
	int status = 0;
	int parse_h = 0;
	int catch_x = 0;
	int catch_y = 0;

	status = optify_init(&argp, argv, argc);
	if (status != OPTIFY_OK)
		fail_msg("State initialization failed for some reason");

	for (;;) {
		status = optify_parse(&argp, optlist, OPTCNT);
		if (status == -OPTIFY_ERR_INVALID_PARAM)
			fail_msg("Invalid parameter(s) passed to parser");
		if (status == OPTIFY_PARSE_END)
			break;
		if (status == OPTIFY_PARSE_CONTINUE)
			continue;

		switch (status) {
		case 'h':
			parse_h = 1;
			break;
		case -OPTIFY_ERR_UNKNOWN_OPT:
			if (strcmp(argp.errarg, "-x") == 0)
				catch_x = 1;
			if (strcmp(argp.errarg, "-y") == 0)
				catch_y = 1;
			break;
		case -OPTIFY_ERR_MISSING_ARG:
			fail_msg("Missing argument %s", argp.errarg);
			break;
		default:
			/* SAFETY: Unreachable case but present for sanity. */
			fail_msg("Hit unmatched case");
			break;
		}
	}

	assert_true(parse_h);
	assert_true(catch_x);
	assert_true(catch_y);
}

/*
 * Test that `optify_parse` can catch known short options.
 *
 * Parser must detect options known within option entry list. A few positionals
 * are thrown in the mix to make sure that the parser does not panic when
 * encountering them.
 */
static void
catch_known_short_option(void **state)
{
	(void)state;
	struct optify argp = {0};
	char *argv[] = { "test", "foo", "-v", "-c", "blue", "-h", NULL };
	int argc = 6;
	int status = 0;
	int parse_c = 0;
	int parse_v = 0;
	int parse_h = 0;

	status = optify_init(&argp, argv, argc);
	if (status != OPTIFY_OK)
		fail_msg("State initialization failed for some reason");

	for (;;) {
		status = optify_parse(&argp, optlist, OPTCNT);
		if (status == -OPTIFY_ERR_INVALID_PARAM)
			fail_msg("Invalid parameter(s) passed to parser");
		if (status == OPTIFY_PARSE_END)
			break;
		if (status == OPTIFY_PARSE_CONTINUE)
			continue;

		switch (status) {
		case 'c':
			parse_c = 1;
			break;
		case 'v':
			parse_v = 1;
			break;
		case 'h':
			parse_h = 1;
			break;
		case -OPTIFY_ERR_UNKNOWN_OPT:
			fail_msg("Unknown option %s", argp.errarg);
			break;
		case -OPTIFY_ERR_MISSING_ARG:
			fail_msg("Missing argument %s", argp.errarg);
			break;
		default:
			/* SAFETY: Unreachable case but present for sanity. */
			fail_msg("Hit unmatched case");
			break;
		}
	}

	assert_true(parse_v);
	assert_true(parse_c);
	assert_true(parse_h);
}

int
main(void)
{
	int result = 0;
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(catch_bad_parameters),
		cmocka_unit_test(catch_unknown_short_option),
		cmocka_unit_test(catch_known_short_option),
	};

	result = cmocka_run_group_tests(tests, NULL, NULL);
	return result;
}
