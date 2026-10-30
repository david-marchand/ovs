/*
 * DOCA DPDK bridge stubs.
 */

#ifndef DOCA_DPDK_H
#define DOCA_DPDK_H

#include "doca_compat.h"
#include "doca_dev.h"

static inline doca_error_t
doca_dpdk_cap_is_rep_port_supported(struct doca_devinfo *devinfo,
                                    uint8_t *is_supported)
{
    (void) devinfo; (void) is_supported;
    return DOCA_ERROR_DRIVER;
}

static inline doca_error_t
doca_dpdk_open_dev_rep_by_port_id(uint16_t port_id, struct doca_dev *dev,
                                  struct doca_dev_rep **rep)
{
    (void) port_id; (void) dev; (void) rep;
    return DOCA_ERROR_DRIVER;
}

#endif /* DOCA_DPDK_H */
