/* SPDX-FileCopyrightText: 2026 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 */

#include "optify.h"

int
optify_init(struct optify *self, char **argv, int argc)
{
	(void)self;
	(void)argc;
	(void)argv;

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
