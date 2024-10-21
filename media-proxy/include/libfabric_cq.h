/*
 * SPDX-FileCopyrightText: Copyright (c) 2024 Intel Corporation
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __LIBFABRIC_CQ_H
#define __LIBFABRIC_CQ_H

#ifdef __cplusplus
extern "C" {
#endif

/* forward declaration */
typedef struct ep_ctx_t ep_ctx_t;

enum cq_comp_method {
    RDMA_COMP_SPIN = 0,
    RDMA_COMP_SREAD,
    RDMA_COMP_WAITSET,
    RDMA_COMP_WAIT_FD,
    RDMA_COMP_YIELD,
};

typedef struct {
    struct fid_cq *cq;
    struct fid_wait *waitset;
    uint64_t cq_cntr;
    int cq_fd;
    int (*eq_read)(ep_ctx_t *ep_ctx, struct fi_cq_err_entry *entry, int timeout);
} cq_ctx_t;

int rdma_cq_open(ep_ctx_t *ep_ctx, size_t cq_size, enum cq_comp_method comp_method);
int rdma_read_cq(ep_ctx_t *ep_ctx, struct fi_cq_err_entry *entry, int timeout);
int rdma_cq_readerr(struct fid_cq *cq);

#ifdef __cplusplus
}
#endif

#endif /* __LIBFABRIC_CQ_H */
