/* SPDX-FileCopyrightText: 2026 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 */

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
	self->optidx = 1;

	return OPTIFY_SUCCESS;
}

int
optify_parse(struct optify *self, struct optify_option *optlist, size_t optcnt)
{
	(void)self;
	(void)optlist;
	(void)optcnt;

	return OPTIFY_PARSE_END;
}
