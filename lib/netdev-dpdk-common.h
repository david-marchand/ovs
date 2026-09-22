/*
 * Copyright (c) 2014, 2015, 2016, 2017 Nicira, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef NETDEV_DPDK_COMMON_H
#define NETDEV_DPDK_COMMON_H

#include <config.h>

#include <linux/if.h>

#include <rte_ether.h>
#include <rte_mempool.h>

struct smap;

/*
 * need to reserve tons of extra space in the mbufs so we can align the
 * DMA addresses to 4KB.
 * The minimum mbuf size is limited to avoid scatter behaviour and drop in
 * performance for standard Ethernet MTU.
 */
#define ETHER_HDR_MAX_LEN           (RTE_ETHER_HDR_LEN + RTE_ETHER_CRC_LEN \
                                     + (2 * VLAN_HEADER_LEN))
#define MTU_TO_FRAME_LEN(mtu)       ((mtu) + RTE_ETHER_HDR_LEN + \
                                     RTE_ETHER_CRC_LEN)
#define MTU_TO_MAX_FRAME_LEN(mtu)   ((mtu) + ETHER_HDR_MAX_LEN)
#define FRAME_LEN_TO_MTU(frame_len) ((frame_len)                    \
                                     - RTE_ETHER_HDR_LEN - RTE_ETHER_CRC_LEN)
#define NETDEV_DPDK_MBUF_ALIGN      1024
#define NETDEV_DPDK_MAX_PKT_LEN     9728

/* Max and min number of packets in the mempool. OVS tries to allocate a
 * mempool with MAX_NB_MBUF: if this fails (because the system doesn't have
 * enough hugepages) we keep halving the number until the allocation succeeds
 * or we reach MIN_NB_MBUF */

#define MAX_NB_MBUF          (4096 * 64)
#define MIN_NB_MBUF          (4096 * 4)
#define MP_CACHE_SZ          RTE_MEMPOOL_CACHE_MAX_SIZE

struct dpdk_mp_config {
    char name[IFNAMSIZ];
    int mtu;
    int socket_id;
    int n_rxq;
    int rxq_size;
    int n_txq;
    int txq_size;
};

void dpdk_mp_init(const struct smap *ovs_other_config);
bool dpdk_mp_per_port_memory(void);
struct rte_mempool *dpdk_mp_get(const struct dpdk_mp_config *cfg);
void dpdk_mp_put(struct rte_mempool *mp);
bool dpdk_mp_dump(FILE *stream, struct rte_mempool *mp);

#endif /* NETDEV_DPDK_COMMON_H */
