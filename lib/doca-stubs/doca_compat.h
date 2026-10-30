/*
 * DOCA SDK compatibility stubs for compilation without the DOCA library.
 * These stubs provide type definitions and function prototypes only.
 *
 * These headers are included before OVS headers, so they must not use
 * OVS macros like OVS_UNUSED.
 */

#ifndef DOCA_COMPAT_H
#define DOCA_COMPAT_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef int doca_error_t;

#define DOCA_SUCCESS                0
#define DOCA_ERROR_UNKNOWN          1
#define DOCA_ERROR_NOT_FOUND        2
#define DOCA_ERROR_INVALID_VALUE    3
#define DOCA_ERROR_IN_PROGRESS      4
#define DOCA_ERROR_DRIVER           5
#define DOCA_ERROR_TIME_OUT         6

static inline const char *
doca_error_get_descr(doca_error_t error)
{
    (void) error;
    return "DOCA stubs: no real library";
}

#endif /* DOCA_COMPAT_H */
