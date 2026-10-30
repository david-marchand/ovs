/*
 * DOCA Flow stubs — type definitions and function prototypes.
 */

#ifndef DOCA_FLOW_H
#define DOCA_FLOW_H

#include "doca_compat.h"
#include "doca_dev.h"

/* Forward declaration needed by doca_flow_cfg_set_definitions(). */
struct doca_flow_definitions;

/* Opaque types. */
struct doca_flow_pipe;
struct doca_flow_pipe_entry;
struct doca_flow_pipe_cfg;
struct doca_flow_port;
struct doca_flow_port_cfg;
struct doca_flow_cfg;
struct doca_flow_target;

/* Forward-declare for action descs. */
struct doca_flow_action_desc;

/* Pipe type enum. */
enum doca_flow_pipe_type {
    DOCA_FLOW_PIPE_BASIC = 0,
    DOCA_FLOW_PIPE_CONTROL,
    DOCA_FLOW_PIPE_LPM,
    DOCA_FLOW_PIPE_CT,
    DOCA_FLOW_PIPE_ACL,
    DOCA_FLOW_PIPE_HASH,
    DOCA_FLOW_PIPE_ORDERED_LIST,
};

/* Pipe domain. */
enum doca_flow_pipe_domain {
    DOCA_FLOW_PIPE_DOMAIN_DEFAULT = 0,
    DOCA_FLOW_PIPE_DOMAIN_EGRESS,
};

/* Entry operation. */
enum doca_flow_entry_op {
    DOCA_FLOW_ENTRY_OP_ADD = 0,
    DOCA_FLOW_ENTRY_OP_DEL,
    DOCA_FLOW_ENTRY_OP_UPD,
    DOCA_FLOW_ENTRY_OP_AGED,
};

/* Entry status. */
enum doca_flow_entry_status {
    DOCA_FLOW_ENTRY_STATUS_IN_PROCESS = 0,
    DOCA_FLOW_ENTRY_STATUS_SUCCESS,
    DOCA_FLOW_ENTRY_STATUS_ERROR,
};

/* Entry flags. */
#define DOCA_FLOW_ENTRY_FLAGS_NO_WAIT 0
#define DOCA_FLOW_FLAGS_IS_SET(flags, flag) ((flags) & (flag))

/* Forwarding type. */
enum doca_flow_fwd_type {
    DOCA_FLOW_FWD_RSS = 0,
    DOCA_FLOW_FWD_PORT,
    DOCA_FLOW_FWD_PIPE,
    DOCA_FLOW_FWD_TARGET,
};

/* RSS flags. */
#define DOCA_FLOW_RSS_IPV4 (1 << 0)
#define DOCA_FLOW_RSS_IPV6 (1 << 1)
#define DOCA_FLOW_RSS_TCP  (1 << 2)
#define DOCA_FLOW_RSS_UDP  (1 << 3)

/* Target. */
#define DOCA_FLOW_TARGET_KERNEL 0

/* Resource / counter types. */
enum doca_flow_resource_type {
    DOCA_FLOW_RESOURCE_TYPE_NON_SHARED = 0,
};

enum doca_flow_resource_mode {
    DOCA_FLOW_RESOURCE_MODE_PORT = 0,
};

#define DOCA_FLOW_RESOURCE_COUNTER 1

/* L2/L3/L4 meta values. */
#define DOCA_FLOW_L2_META_NO_VLAN  0
#define DOCA_FLOW_L3_META_NONE     0
#define DOCA_FLOW_L3_META_IPV4     1
#define DOCA_FLOW_L3_META_IPV6     2
#define DOCA_FLOW_L4_META_NONE     0
#define DOCA_FLOW_L4_META_TCP      1
#define DOCA_FLOW_L4_META_UDP      2
#define DOCA_FLOW_L4_META_ICMP     3
#define DOCA_FLOW_L4_META_ESP      4

/* --- Non-opaque structs with field access --- */

typedef uint32_t doca_be32_t;

struct doca_flow_meta {
    union {
        uint32_t pkt_meta;
        uint32_t u32[1];
    };
};

enum doca_flow_l3_meta {
    DOCA_FLOW_L3_META_NONE_VAL = 0,
    DOCA_FLOW_L3_META_IPV4_VAL,
    DOCA_FLOW_L3_META_IPV6_VAL,
};

enum doca_flow_l4_meta {
    DOCA_FLOW_L4_META_NONE_VAL = 0,
    DOCA_FLOW_L4_META_TCP_VAL,
    DOCA_FLOW_L4_META_UDP_VAL,
    DOCA_FLOW_L4_META_ICMP_VAL,
    DOCA_FLOW_L4_META_ESP_VAL,
};

struct doca_flow_parser_meta {
    uint32_t outer_l2_type;
    enum doca_flow_l3_meta outer_l3_type;
    enum doca_flow_l4_meta outer_l4_type;
    uint16_t port_id;
};

struct doca_flow_eth_hdr {
    uint16_t type;
};

struct doca_flow_outer {
    struct doca_flow_eth_hdr eth;
};

struct doca_flow_match {
    struct doca_flow_meta meta;
    struct doca_flow_parser_meta parser_meta;
    struct doca_flow_outer outer;
};

struct doca_flow_actions {
    struct doca_flow_meta meta;
    uint32_t mark;
};

struct doca_flow_fwd_rss {
    uint16_t *queues_array;
    int nr_queues;
    uint32_t outer_flags;
};

struct doca_flow_fwd {
    enum doca_flow_fwd_type type;
    union {
        struct {
            uint16_t port_id;
        };
        struct {
            struct doca_flow_pipe *next_pipe;
        };
        struct {
            struct doca_flow_target *target;
        };
    };
    uint32_t rss_type;
    struct doca_flow_fwd_rss rss;
};

struct doca_flow_monitor {
    uint32_t counter_type;
};

struct doca_flow_counter {
    uint64_t total_bytes;
    uint64_t total_pkts;
};

struct doca_flow_resource_query {
    struct doca_flow_counter counter;
};

struct doca_flow_action_descs {
    struct doca_flow_action_desc *desc_array;
    int nb_action_desc;
};

/* Entry process callback type. */
typedef void (*doca_flow_entry_process_cb)(
    struct doca_flow_pipe_entry *entry,
    uint16_t pipe_queue,
    enum doca_flow_entry_status status,
    enum doca_flow_entry_op op,
    void *user_ctx);

/* --- Flow configuration API --- */

static inline doca_error_t
doca_flow_cfg_create(struct doca_flow_cfg **cfg)
{
    (void) cfg;
    return DOCA_ERROR_DRIVER;
}

static inline doca_error_t
doca_flow_cfg_destroy(struct doca_flow_cfg *cfg)
{
    (void) cfg;
    return DOCA_SUCCESS;
}

static inline doca_error_t
doca_flow_cfg_set_pipe_queues(struct doca_flow_cfg *cfg, uint16_t nr_queues)
{
    (void) cfg; (void) nr_queues;
    return DOCA_ERROR_DRIVER;
}

static inline doca_error_t
doca_flow_cfg_set_queue_depth(struct doca_flow_cfg *cfg, uint32_t depth)
{
    (void) cfg; (void) depth;
    return DOCA_ERROR_DRIVER;
}

static inline doca_error_t
doca_flow_cfg_set_resource_mode(struct doca_flow_cfg *cfg,
                                enum doca_flow_resource_mode mode)
{
    (void) cfg; (void) mode;
    return DOCA_ERROR_DRIVER;
}

static inline doca_error_t
doca_flow_cfg_set_mode_args(struct doca_flow_cfg *cfg, const char *args)
{
    (void) cfg; (void) args;
    return DOCA_ERROR_DRIVER;
}

static inline doca_error_t
doca_flow_cfg_set_cb_entry_process(struct doca_flow_cfg *cfg,
                                   doca_flow_entry_process_cb cb)
{
    (void) cfg; (void) cb;
    return DOCA_ERROR_DRIVER;
}

static inline doca_error_t
doca_flow_cfg_set_definitions(struct doca_flow_cfg *cfg,
                              struct doca_flow_definitions *defs)
{
    (void) cfg; (void) defs;
    return DOCA_ERROR_DRIVER;
}

static inline doca_error_t
doca_flow_cfg_set_nr_resources(struct doca_flow_cfg *cfg,
                               uint32_t nr_counters, uint32_t type)
{
    (void) cfg; (void) nr_counters; (void) type;
    return DOCA_ERROR_DRIVER;
}

static inline doca_error_t
doca_flow_init(struct doca_flow_cfg *cfg)
{
    (void) cfg;
    return DOCA_ERROR_DRIVER;
}

/* --- Port configuration API --- */

static inline doca_error_t
doca_flow_port_cfg_create(struct doca_flow_port_cfg **cfg)
{
    (void) cfg;
    return DOCA_ERROR_DRIVER;
}

static inline doca_error_t
doca_flow_port_cfg_destroy(struct doca_flow_port_cfg *cfg)
{
    (void) cfg;
    return DOCA_SUCCESS;
}

static inline doca_error_t
doca_flow_port_cfg_set_dev(struct doca_flow_port_cfg *cfg,
                           struct doca_dev *dev)
{
    (void) cfg; (void) dev;
    return DOCA_ERROR_DRIVER;
}

static inline doca_error_t
doca_flow_port_cfg_set_dev_rep(struct doca_flow_port_cfg *cfg,
                               struct doca_dev_rep *rep)
{
    (void) cfg; (void) rep;
    return DOCA_ERROR_DRIVER;
}

static inline doca_error_t
doca_flow_port_cfg_set_port_id(struct doca_flow_port_cfg *cfg,
                               uint16_t port_id)
{
    (void) cfg; (void) port_id;
    return DOCA_ERROR_DRIVER;
}

static inline doca_error_t
doca_flow_port_cfg_set_actions_mem_size(struct doca_flow_port_cfg *cfg,
                                        uint32_t size)
{
    (void) cfg; (void) size;
    return DOCA_ERROR_DRIVER;
}

static inline doca_error_t
doca_flow_port_cfg_set_nr_resources(struct doca_flow_port_cfg *cfg,
                                    uint32_t nr_counters, uint32_t type)
{
    (void) cfg; (void) nr_counters; (void) type;
    return DOCA_ERROR_DRIVER;
}

static inline doca_error_t
doca_flow_port_start(struct doca_flow_port_cfg *cfg,
                     struct doca_flow_port **port)
{
    (void) cfg; (void) port;
    return DOCA_ERROR_DRIVER;
}

static inline doca_error_t
doca_flow_port_stop(struct doca_flow_port *port)
{
    (void) port;
    return DOCA_SUCCESS;
}

static inline struct doca_flow_port *
doca_flow_port_switch_get(struct doca_flow_port *port)
{
    (void) port;
    return NULL;
}

/* --- Pipe configuration API --- */

static inline doca_error_t
doca_flow_pipe_cfg_create(struct doca_flow_pipe_cfg **cfg,
                          struct doca_flow_port *port)
{
    (void) cfg; (void) port;
    return DOCA_ERROR_DRIVER;
}

static inline doca_error_t
doca_flow_pipe_cfg_destroy(struct doca_flow_pipe_cfg *cfg)
{
    (void) cfg;
    return DOCA_SUCCESS;
}

static inline doca_error_t
doca_flow_pipe_cfg_set_name(struct doca_flow_pipe_cfg *cfg, const char *name)
{
    (void) cfg; (void) name;
    return DOCA_ERROR_DRIVER;
}

static inline doca_error_t
doca_flow_pipe_cfg_set_type(struct doca_flow_pipe_cfg *cfg,
                            enum doca_flow_pipe_type type)
{
    (void) cfg; (void) type;
    return DOCA_ERROR_DRIVER;
}

static inline doca_error_t
doca_flow_pipe_cfg_set_nr_entries(struct doca_flow_pipe_cfg *cfg,
                                  uint32_t nr_entries)
{
    (void) cfg; (void) nr_entries;
    return DOCA_ERROR_DRIVER;
}

static inline doca_error_t
doca_flow_pipe_cfg_set_match(struct doca_flow_pipe_cfg *cfg,
                             const struct doca_flow_match *match,
                             const struct doca_flow_match *mask)
{
    (void) cfg; (void) match; (void) mask;
    return DOCA_ERROR_DRIVER;
}

static inline doca_error_t
doca_flow_pipe_cfg_set_actions(struct doca_flow_pipe_cfg *cfg,
                               struct doca_flow_actions **actions,
                               struct doca_flow_actions **masks,
                               struct doca_flow_action_descs **descs,
                               uint32_t nb_actions)
{
    (void) cfg; (void) actions; (void) masks; (void) descs;
    (void) nb_actions;
    return DOCA_ERROR_DRIVER;
}

static inline doca_error_t
doca_flow_pipe_cfg_set_monitor(struct doca_flow_pipe_cfg *cfg,
                               const struct doca_flow_monitor *mon)
{
    (void) cfg; (void) mon;
    return DOCA_ERROR_DRIVER;
}

static inline doca_error_t
doca_flow_pipe_cfg_set_domain(struct doca_flow_pipe_cfg *cfg,
                              enum doca_flow_pipe_domain domain)
{
    (void) cfg; (void) domain;
    return DOCA_ERROR_DRIVER;
}

static inline doca_error_t
doca_flow_pipe_cfg_set_is_root(struct doca_flow_pipe_cfg *cfg, bool is_root)
{
    (void) cfg; (void) is_root;
    return DOCA_ERROR_DRIVER;
}

static inline doca_error_t
doca_flow_pipe_cfg_set_excluded_queue(struct doca_flow_pipe_cfg *cfg,
                                      uint16_t queue)
{
    (void) cfg; (void) queue;
    return DOCA_ERROR_DRIVER;
}

static inline doca_error_t
doca_flow_pipe_create(struct doca_flow_pipe_cfg *cfg,
                      const struct doca_flow_fwd *fwd,
                      const struct doca_flow_fwd *fwd_miss,
                      struct doca_flow_pipe **pipe)
{
    (void) cfg; (void) fwd; (void) fwd_miss; (void) pipe;
    return DOCA_ERROR_DRIVER;
}

static inline void
doca_flow_pipe_destroy(struct doca_flow_pipe *pipe)
{
    (void) pipe;
}

/* --- Entry API --- */

static inline doca_error_t
doca_flow_pipe_basic_add_entry(uint16_t pipe_queue,
                               struct doca_flow_pipe *pipe,
                               const struct doca_flow_match *match,
                               uint32_t action_idx,
                               const struct doca_flow_actions *actions,
                               const struct doca_flow_monitor *monitor,
                               const struct doca_flow_fwd *fwd,
                               uint32_t flags, void *user_ctx,
                               struct doca_flow_pipe_entry **entry)
{
    (void) pipe_queue; (void) pipe; (void) match; (void) action_idx;
    (void) actions; (void) monitor; (void) fwd; (void) flags;
    (void) user_ctx; (void) entry;
    return DOCA_ERROR_DRIVER;
}

static inline doca_error_t
doca_flow_pipe_hash_add_entry(uint16_t pipe_queue,
                              struct doca_flow_pipe *pipe,
                              uint32_t entry_index,
                              uint32_t action_idx,
                              const struct doca_flow_actions *actions,
                              const struct doca_flow_monitor *monitor,
                              const struct doca_flow_fwd *fwd,
                              uint32_t flags, void *user_ctx,
                              struct doca_flow_pipe_entry **entry)
{
    (void) pipe_queue; (void) pipe; (void) entry_index; (void) action_idx;
    (void) actions; (void) monitor; (void) fwd; (void) flags;
    (void) user_ctx; (void) entry;
    return DOCA_ERROR_DRIVER;
}

static inline doca_error_t
doca_flow_pipe_remove_entry(uint16_t pipe_queue, uint32_t flags,
                            struct doca_flow_pipe_entry *entry)
{
    (void) pipe_queue; (void) flags; (void) entry;
    return DOCA_ERROR_DRIVER;
}

static inline enum doca_flow_entry_status
doca_flow_pipe_entry_get_status(struct doca_flow_pipe_entry *entry)
{
    (void) entry;
    return DOCA_FLOW_ENTRY_STATUS_ERROR;
}

static inline doca_error_t
doca_flow_entries_process(struct doca_flow_port *port, uint16_t pipe_queue,
                          uint32_t timeout, uint32_t max_processed)
{
    (void) port; (void) pipe_queue; (void) timeout; (void) max_processed;
    return DOCA_ERROR_DRIVER;
}

static inline doca_error_t
doca_flow_resource_query_entry(struct doca_flow_pipe_entry *entry,
                               struct doca_flow_resource_query *query)
{
    (void) entry; (void) query;
    return DOCA_ERROR_DRIVER;
}

static inline doca_error_t
doca_flow_get_target(uint32_t target_type, struct doca_flow_target **target)
{
    (void) target_type; (void) target;
    return DOCA_ERROR_DRIVER;
}

#endif /* DOCA_FLOW_H */
