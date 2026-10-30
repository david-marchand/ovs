/*
 * DOCA logging stubs.
 */

#ifndef DOCA_LOG_H
#define DOCA_LOG_H

#include "doca_compat.h"
#include <stdio.h>

enum doca_log_level {
    DOCA_LOG_LEVEL_DISABLE = 0,
    DOCA_LOG_LEVEL_CRIT,
    DOCA_LOG_LEVEL_ERROR,
    DOCA_LOG_LEVEL_WARNING,
    DOCA_LOG_LEVEL_INFO,
    DOCA_LOG_LEVEL_DEBUG,
    DOCA_LOG_LEVEL_TRACE,
};

struct doca_log_backend;

static inline enum doca_log_level
doca_log_level_get_global_sdk_limit(void)
{
    return DOCA_LOG_LEVEL_DISABLE;
}

static inline doca_error_t
doca_log_level_set_global_sdk_limit(enum doca_log_level level)
{
    (void) level;
    return DOCA_SUCCESS;
}

static inline const char *
doca_log_level_to_str(enum doca_log_level level)
{
    (void) level;
    return "disabled";
}

static inline doca_error_t
doca_log_backend_create_with_file_sdk(FILE *fptr,
                                      struct doca_log_backend **backend)
{
    (void) fptr; (void) backend;
    return DOCA_ERROR_DRIVER;
}

#endif /* DOCA_LOG_H */
