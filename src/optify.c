/* SPDX-FileCopyrightText: 2026 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 */

#include <string.h>

#include "optify.h"

int
optify_init(struct optify *self, char **argv, int argc)
{
	if (!self || !argv)
		return -OPTIFY_BAD_API_USE;

	self->argv = argv;
	self->optarg = NULL;
	self->errarg = NULL;
	self->argc = argc;
	/* INVARIANT: Start at argv[1], because argv[0] is the program name. */
	self->optidx = 1;

	return OPTIFY_SUCCESS;
}

static inline int
is_short_option(const char *arg)
{
	return arg != NULL && arg[0] == '-' && arg[1] != '-' && arg[1] != '\0';
}

static inline int
is_option_entry_empty(const struct optify_option *entry)
{
	return entry->shortid != 0 && entry->longid != NULL &&
	       entry->argkind != 0;
}

static const struct optify_option *
get_short_option_entry(const char *arg, const struct optify_option *optlist,
	               size_t optcnt)
{
	const struct optify_option *opt = NULL;
	const struct optify_option *end = optlist + optcnt;

	if (!arg || !optlist)
		return NULL;

	/*
	 * SAFETY: Remain in bounds of option entry list.
	 *   - Length check takes precedence over NULL termination check in
	 *     case caller submits an option list with no NULL terminator.
	 */
	for (opt = optlist; opt < end && !is_option_entry_empty(opt); ++opt)
		if (arg[1] == opt->shortid)
			return opt;

	return NULL;
}

int
optify_parse(struct optify *self, const struct optify_option *optlist, size_t optcnt)
{
	const struct optify_option *opt = NULL;
	char *arg = NULL;

	if (!self || !optlist)
		return -OPTIFY_BAD_API_USE;

	self->optarg = NULL;
	self->errarg = NULL;
	arg = self->argv[self->optidx];

	/*
	 * INVARIANT: Stop parsing iff we reach the end of argv.
	 *   - C standard ensures argv is NULL terminated so length check is
	 *     technically redundant, but I am very paranoid :3
	 */
	if (!arg || self->optidx == self->argc)
		return OPTIFY_PARSE_END;

	if (is_short_option(arg)) {
		opt = get_short_option_entry(arg, optlist, optcnt);
		if (!opt) {
			self->errarg = arg;
			/* INVARIANT: Move forward; let caller handle this. */
			++self->optidx;
			return -OPTIFY_UNKNOWN_OPT;
		}

		++self->optidx;
		return opt->shortid;
	}

	++self->optidx;
	return OPTIFY_PARSE_CONTINUE;
}
