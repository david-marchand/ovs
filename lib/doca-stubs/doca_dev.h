/*
 * DOCA device management stubs.
 */

#ifndef DOCA_DEV_H
#define DOCA_DEV_H

#include "doca_compat.h"

#define DOCA_DEVINFO_IFACE_NAME_SIZE 256
#define DOCA_DEVINFO_REP_FILTER_NET  (1 << 0)

struct doca_dev;
struct doca_dev_rep;
struct doca_devinfo;
struct doca_devinfo_rep;

struct doca_pci_addr {
    uint32_t domain;
    uint8_t bus;
    uint8_t devid;
    uint8_t function;
};

static inline doca_error_t
doca_dev_open(struct doca_devinfo *devinfo, struct doca_dev **dev)
{
    (void) devinfo; (void) dev;
    return DOCA_ERROR_DRIVER;
}

static inline doca_error_t
doca_dev_open_pci(const struct doca_pci_addr *pci, struct doca_dev **dev)
{
    (void) pci; (void) dev;
    return DOCA_ERROR_DRIVER;
}

static inline doca_error_t
doca_dev_close(struct doca_dev *dev)
{
    (void) dev;
    return DOCA_SUCCESS;
}

static inline doca_error_t
doca_dev_rep_close(struct doca_dev_rep *rep)
{
    (void) rep;
    return DOCA_SUCCESS;
}

static inline doca_error_t
doca_devinfo_create_list(struct doca_devinfo ***list, uint32_t *nb_devs)
{
    (void) list; (void) nb_devs;
    return DOCA_ERROR_DRIVER;
}

static inline doca_error_t
doca_devinfo_destroy_list(struct doca_devinfo **list)
{
    (void) list;
    return DOCA_SUCCESS;
}

static inline doca_error_t
doca_devinfo_get_iface_name(const struct doca_devinfo *devinfo, char *name,
                            uint32_t size)
{
    (void) devinfo; (void) name; (void) size;
    return DOCA_ERROR_DRIVER;
}

static inline doca_error_t
doca_devinfo_get_pci_addr_str(const struct doca_devinfo *devinfo,
                              char *pci_addr)
{
    (void) devinfo; (void) pci_addr;
    return DOCA_ERROR_DRIVER;
}

static inline doca_error_t
doca_devinfo_is_equal_pci_addr(const struct doca_devinfo *devinfo,
                               const char *pci_addr_str,
                               uint8_t *is_equal)
{
    (void) devinfo; (void) pci_addr_str; (void) is_equal;
    return DOCA_ERROR_DRIVER;
}

static inline doca_error_t
doca_devinfo_rep_cap_is_filter_net_supported(
    const struct doca_devinfo *devinfo, uint8_t *is_supported)
{
    (void) devinfo; (void) is_supported;
    return DOCA_ERROR_DRIVER;
}

static inline doca_error_t
doca_devinfo_rep_create_list(struct doca_dev *dev, uint32_t filter,
                             struct doca_devinfo_rep ***list,
                             uint32_t *nb_devs)
{
    (void) dev; (void) filter; (void) list; (void) nb_devs;
    return DOCA_ERROR_DRIVER;
}

static inline doca_error_t
doca_devinfo_rep_destroy_list(struct doca_devinfo_rep **list)
{
    (void) list;
    return DOCA_SUCCESS;
}

static inline doca_error_t
doca_devinfo_rep_get_iface_name(const struct doca_devinfo_rep *devinfo,
                                char *name, uint32_t size)
{
    (void) devinfo; (void) name; (void) size;
    return DOCA_ERROR_DRIVER;
}

#endif /* DOCA_DEV_H */
