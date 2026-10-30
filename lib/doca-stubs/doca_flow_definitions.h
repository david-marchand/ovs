/*
 * DOCA flow definitions stubs.
 */

#ifndef DOCA_FLOW_DEFINITIONS_H
#define DOCA_FLOW_DEFINITIONS_H

#include "doca_compat.h"

struct doca_flow_definitions;
struct doca_flow_definitions_cfg;

static inline doca_error_t
doca_flow_definitions_cfg_create(struct doca_flow_definitions_cfg **cfg)
{
    (void) cfg;
    return DOCA_ERROR_DRIVER;
}

static inline doca_error_t
doca_flow_definitions_cfg_destroy(struct doca_flow_definitions_cfg *cfg)
{
    (void) cfg;
    return DOCA_SUCCESS;
}

static inline doca_error_t
doca_flow_definitions_create(struct doca_flow_definitions_cfg *cfg,
                             struct doca_flow_definitions **defs)
{
    (void) cfg; (void) defs;
    return DOCA_ERROR_DRIVER;
}

static inline doca_error_t
doca_flow_definitions_destroy(struct doca_flow_definitions *defs)
{
    (void) defs;
    return DOCA_SUCCESS;
}

static inline doca_error_t
doca_flow_definitions_add_field(struct doca_flow_definitions *defs,
                                const char *name, uint32_t bit_size,
                                uint32_t offset)
{
    (void) defs; (void) name; (void) bit_size; (void) offset;
    return DOCA_ERROR_DRIVER;
}

#endif /* DOCA_FLOW_DEFINITIONS_H */
