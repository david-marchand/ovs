/*
 * DOCA RDMA bridge stubs.
 */

#ifndef DOCA_RDMA_BRIDGE_H
#define DOCA_RDMA_BRIDGE_H

#include "doca_compat.h"
#include "doca_dev.h"

struct ibv_pd;

static inline doca_error_t
doca_rdma_bridge_get_dev_pd(struct doca_dev *dev, struct ibv_pd **pd)
{
    (void) dev; (void) pd;
    return DOCA_ERROR_DRIVER;
}

#endif /* DOCA_RDMA_BRIDGE_H */
