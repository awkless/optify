/* SPDX-FileCopyrightText: 2026 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 */

#include <string.h>

#include "optify.h"

int
optify_init(struct optify *self, char **argv, int argc)
{
	if (!self || !argv)
		return -OPTIFY_ERR_INVALID_PARAM;

	self->argv = argv;
	self->optarg = NULL;
	self->errarg = NULL;
	self->argc = argc;
	/* INVARIANT: Start at argv[1], because argv[0] is the program name. */
	self->optidx = 1;

	return OPTIFY_OK;
}

static inline int
is_short_option(const char *arg)
{
	return arg && arg[0] == '-' && arg[1] != '-' && arg[1] != '\0';
}

static int
is_positional(const char *arg)
{
	return arg && arg[0] != '-' && arg[0] != '\0';
}

static inline int
is_option_entry_empty(const struct optify_option *entry)
{
	return entry->shortid == 0 && entry->longid == NULL &&
	       entry->argkind == 0;
}

static const struct optify_option *
get_short_option_entry(const char *arg, const struct optify_option *optlist,
	               size_t optcnt)
{
	if (!arg || !optlist)
		return NULL;

	/*
	 * SAFETY: Remain in bounds of option entry list.
	 *   - Length check takes precedence over NULL termination check in
	 *     case caller submits an option list with no NULL terminator.
	 */
	const struct optify_option *opt = NULL;
	const struct optify_option *end = optlist + optcnt;
	for (opt = optlist; opt < end && !is_option_entry_empty(opt); ++opt)
		if (arg[1] == opt->shortid)
			return opt;

	return NULL;
}

static int
parse_option_arg(struct optify *self, char *arg, int argkind)
{
	int peek_pos = 0;
	char *peek_arg = NULL;

	if (!self)
		return -OPTIFY_ERR_INVALID_PARAM;

	if (argkind == OPTIFY_NO_ARG)
		return OPTIFY_OK;

	peek_pos = self->optidx + 1;
	peek_arg = self->argv[peek_pos];

	if (argkind == OPTIFY_REQUIRED_ARG) {
		if (peek_pos >= self->argc || !peek_arg || !is_positional(peek_arg)) {
			self->errarg = arg;
			self->optarg = NULL;
			self->optidx = peek_pos;
			return -OPTIFY_ERR_MISSING_ARG;
		}

	}

	if (argkind == OPTIFY_OPTIONAL_ARG) {
		if (peek_pos >= self->argc || !peek_arg || !is_positional(peek_arg)) {
			self->errarg = NULL;
			self->optarg = NULL;
			return OPTIFY_OK;
		}
	}

	self->optarg = peek_arg;
	self->optidx = peek_pos;

	return OPTIFY_OK;
}

int
optify_parse(struct optify *self, const struct optify_option *optlist, size_t optcnt)
{
	const struct optify_option *opt = NULL;
	char *arg = NULL;
	int status = OPTIFY_OK;

	if (!self || !optlist)
		return -OPTIFY_ERR_INVALID_PARAM;

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
			self->optidx++;
			return -OPTIFY_ERR_UNKNOWN_OPT;
		}

		status = parse_option_arg(self, arg, opt->argkind);
		if (status != OPTIFY_OK)
			return status;

		self->optidx++;
		return opt->shortid;
	}

	self->optidx++;

	return OPTIFY_PARSE_CONTINUE;
}
