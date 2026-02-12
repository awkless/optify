/* SPDX-FileCopyrightText: 2026 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 */

#ifndef OPTIFY_H
#define OPTIFY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#include "optify_export.h"

/** \brief Use this to mark the end of an option list. */
#define OPTIFY_OPTLIST_END { .shortid = 0, .longid = NULL, .argkind = 0 }

enum {
	/** \brief Mark option as having no argument. */
	OPTIFY_NO_ARG = 0,

	/** \brief Mark option as having a mandatory argument. */
	OPTIFY_REQUIRED_ARG = 1,

	/** \brief Mark option as having an optional argument. */
	OPTIFY_OPTIONAL_ARG = 2,
};

enum {
	/** \brief Parser finished parsing command-line arguments. */
	OPTIFY_PARSE_END = 0,

	/** \brief Parser did not encounter an option, but still parsing. */
	OPTIFY_PARSE_CONTINUE = 1,
};

enum {
	/** \brief API call successful, i.e., no errors. */
	OPTIFY_SUCCESS = 0,

	/** \brief API was missued, e.g., given NULL parameter. */
	OPTIFY_BAD_API_USE = 1,

	/** \brief Parser encountered an option not in option list. */
	OPTIFY_UNKNOWN_OPT = 2,

	/** \brief Parser encountered an option missing a required argument. */
	OPTIFY_MISSING_ARG = 3,
};

/**
 * \brief Option entry.
 *
 * User is responsible for allocating memory and maintaining ownership of all
 * option entries they define.
 *
 * \precondition The `shortid` member must be greater than one.
 * \invariant Use `shortid` to identify an option entry.
 * \invariant All members are immutable.
 * \invariant If `longid` is NULL, `shortid` is zero, and `argkind` is zero,
 *            then option entry designates the end of an option list.
 */
struct optify_option {
	/** \brief Long name of option entry. */
	const char *longid;

	/** \brief Short name of option entry. */
	int shortid;

	/** \brief Argument settings of an option entry. */
	int argkind;
};

/**
 * \brief Parser state.
 *
 * User is responsible for allocating memory and maintaining ownership of this
 * parser state. User can directly read the contents of their parser state, but
 * should not directly modify it. Instead, they should allow API calls to
 * modify their parser state when needed.
 *
 * \invariant The members `argv`, `optarg`, `errarg`, and `optidx` are mutable.
 * \invariant The `argc` member is immutable.
 */
struct optify {
	/** \brief List of command-line arguments to parse. */
	char **argv;

	/** \brief Pointer to option argument. */
	char *optarg;

	/** \brief Pointer to argument causing trouble. */
	char *errarg;

	/** \brief Number of command-line arguments to parse. */
	int argc;

	/** \brief Current index being parsed in command-line argument list. */
	int optidx;
};

/**
 * \brief Initialize parser state.
 *
 * Takes parser state and properly initializes it. Assumes that the caller
 * properly allocated the memory for the parser context beforehand.
 *
 * \param[in,out] self _[mutable reference]_ Parser state to initialize.
 * \param[in] argc _[immutable copy]_ Number of arguments to parse.
 * \param[in] argv _[mutable reference]_ List of arguments to parse.
 * \return Returns `OPTIFY_SUCCESS` for no errors.
 * \return Returns `-OPTIFY_BAD_API_USE` iff `self` or `argv` is NULL.
 */
OPTIFY_EXPORT int
optify_init(struct optify *self, char **argv, int argc);

/**
 * \brief Parse next command-line argument.
 *
 * Parses _only_ the next command-line argument available. It stops and returns
 * status to allow for the caller to perform syntax directed semantic action.
 * Caller is responsible for determining error handling behavior, i.e., decide
 * between fail fast, fail forward, etc.
 *
 * Positionals get permuted to the right of the command-line argument list such
 * that options and their arguments get shifted leftward. Thus, all positionals
 * come after options once parsing is done. At the end of parsing, the parser
 * state will point to the first permuted positional.
 *
 * \param[in,out] self _[mutable reference]_ Parser state to utilize.
 * \param[in] optlist _[immutable reference]_ List of options to parse for.
 * \param[in] optcnt _[immutable copy]_ Number of options in option list.
 * \return Returns `OPTIFY_PARSE_END` when it reaches the end of the
 *         command-line argument list.
 * \return Returns `OPTIFY_PARSE_CONTINUE` if it did not detect any options to
 *         parse (may still permute positionals).
 * \return Returns short ID of an option it parsed.
 * \return Returns `-OPTIFY_BAD_API_USE` iff `self` or `optlist` is NULL.
 * \return Returns `-OPTIFY_MISSING_ARG` iff parsed option is missing a
 *         required argument.
 * \return Returns `-OPTIFY_UNKNOWN_OPT` iff detected option does not exist in
 *         option list.
 */
OPTIFY_EXPORT int
optify_parse(struct optify *self, struct optify_option *optlist, size_t optcnt);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* OPTIFY_H */
