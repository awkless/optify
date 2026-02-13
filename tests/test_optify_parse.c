/* SPDX-FileCopyrightText: 2026 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 */

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <stdlib.h>
#include <string.h>
#include <cmocka.h>

#include <optify.h>

#define OPTCNT 3

static const struct optify_option optlist_fixture[] = {
	{ .shortid = 'b', .longid = "bar", .argkind = OPTIFY_NO_ARG },
	{ .shortid = 'f', .longid = "foo", .argkind = OPTIFY_NO_ARG },
	{ .shortid = 'h', .longid = "help", .argkind = OPTIFY_NO_ARG },
	OPTIFY_OPTLIST_END
};

struct parser_state {
	struct optify argp;
	const struct optify_option *optlist;
};

static int
setup_parser(void **state)
{
	struct parser_state *pstate = malloc(sizeof *pstate);
	if (!pstate)
		return 1;

	pstate->argp = (struct optify){ 0 };
	pstate->optlist = optlist_fixture;
	*state = pstate;

	return 0;
}

static int
teardown_parser(void **state)
{
	struct parser_state *pstate = *state;
	free(pstate);
	return 0;
}

static void
catch_bad_parameters(void **state)
{
	struct parser_state *pstate = *state;
	char *argv[] = { "test", NULL };
	int argc = 1;
	int result = 0;

	result = optify_init(&pstate->argp, argv, argc);
	if (result != OPTIFY_SUCCESS)
		fail_msg("State initialization failed for some reason");

	result = optify_parse(NULL, NULL, 0);
	assert_int_equal(result, -OPTIFY_BAD_API_USE);

	result = optify_parse(&pstate->argp, NULL, 0);
	assert_int_equal(result, -OPTIFY_BAD_API_USE);

	result = optify_parse(NULL, pstate->optlist, OPTCNT);
	assert_int_equal(result, -OPTIFY_BAD_API_USE);

	result = optify_parse(&pstate->argp, pstate->optlist, OPTCNT);
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
	struct parser_state *pstate = *state;
	char *argv[] = { "test", "foo", "-x", "-h", "bar", "-y", NULL };
	int argc = 6;
	int status = 0;
	int parse_h = 0;
	int catch_x = 0;
	int catch_y = 0;

	status = optify_init(&pstate->argp, argv, argc);
	if (status != OPTIFY_SUCCESS)
		fail_msg("State initialization failed for some reason");

	for (;;) {
		status = optify_parse(&pstate->argp, pstate->optlist, OPTCNT);
		if (status == -OPTIFY_BAD_API_USE)
			fail_msg("Invalid parameter(s) passed to parser");
		if (status == OPTIFY_PARSE_END)
			break;
		if (status == OPTIFY_PARSE_CONTINUE)
			continue;

		switch (status) {
		case 'h':
			parse_h = 1;
			break;
		case -OPTIFY_UNKNOWN_OPT:
			if (strcmp(pstate->argp.errarg, "-x") == 0)
				catch_x = 1;
			if (strcmp(pstate->argp.errarg, "-y") == 0)
				catch_y = 1;
			break;
		case -OPTIFY_MISSING_ARG:
			fail_msg("Missing argument %s", pstate->argp.errarg);
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
	struct parser_state *pstate = *state;
	char *argv[] = { "test", "foo", "-b", "-f", "bar", "-h", NULL };
	int argc = 6;
	int status = 0;
	int parse_b = 0;
	int parse_f = 0;
	int parse_h = 0;

	status = optify_init(&pstate->argp, argv, argc);
	if (status != OPTIFY_SUCCESS)
		fail_msg("State initialization failed for some reason");

	for (;;) {
		status = optify_parse(&pstate->argp, pstate->optlist, OPTCNT);
		if (status == -OPTIFY_BAD_API_USE)
			fail_msg("Invalid parameter(s) passed to parser");
		if (status == OPTIFY_PARSE_END)
			break;
		if (status == OPTIFY_PARSE_CONTINUE)
			continue;

		switch (status) {
		case 'b':
			parse_b = 1;
			break;
		case 'f':
			parse_f = 1;
			break;
		case 'h':
			parse_h = 1;
			break;
		case -OPTIFY_UNKNOWN_OPT:
			fail_msg("Unknown option %s", pstate->argp.errarg);
			break;
		case -OPTIFY_MISSING_ARG:
			fail_msg("Missing argument %s", pstate->argp.errarg);
			break;
		default:
			/* SAFETY: Unreachable case but present for sanity. */
			fail_msg("Hit unmatched case");
			break;
		}
	}

	assert_true(parse_b);
	assert_true(parse_f);
	assert_true(parse_h);
}

int
main(void)
{
	int result = 0;
	const struct CMUnitTest tests[] = {
		cmocka_unit_test_setup_teardown(catch_bad_parameters,
						setup_parser, teardown_parser),
		cmocka_unit_test_setup_teardown(catch_unknown_short_option,
						setup_parser, teardown_parser),
		cmocka_unit_test_setup_teardown(catch_known_short_option,
						setup_parser, teardown_parser),
	};

	result = cmocka_run_group_tests(tests, NULL, NULL);
	return result;
}
