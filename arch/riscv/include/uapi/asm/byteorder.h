/* SPDX-License-Identifier: GPL-2.0-only WITH Linux-syscall-note */
/*
 * Copyright (C) 2012 ARM Ltd.
 * Copyright (C) 2015 Regents of the University of California
 */

#ifndef _UAPI_ASM_RISCV_BYTEORDER_H
#define _UAPI_ASM_RISCV_BYTEORDER_H

#ifdef CONFIG_CPU_BIG_ENDIAN
#include <linux/byteorder/big_endian.h>
#else
#include <linux/byteorder/little_endian.h>
#endif

#endif /* _UAPI_ASM_RISCV_BYTEORDER_H */
