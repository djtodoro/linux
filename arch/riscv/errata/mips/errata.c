// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (C) 2024 MIPS.
 */

#include <linux/memory.h>
#include <linux/module.h>

#include <asm/alternative.h>
#include <asm/cacheflush.h>
#include <asm/errata_list.h>
#include <asm/text-patching.h>
#include <asm/processor.h>
#include <asm/sbi.h>
#include <asm/vendorid_list.h>
#include <asm/vendor_extensions.h>

void __init_or_module mips_errata_patch_func(struct alt_entry *begin,
					     struct alt_entry *end,
					     unsigned long archid,
					     unsigned long impid,
					     unsigned int stage)
{
	if (!IS_ENABLED(CONFIG_ERRATA_MIPS))
		return;

	if (!IS_ENABLED(CONFIG_ERRATA_MIPS_P8700_PAUSE_OPCODE))
		return;

	asm volatile(ALTERNATIVE(".4byte 0x1000000f", ".4byte 0x00501013",
				 MIPS_VENDOR_ID, 0, /* patch_id */
				 CONFIG_ERRATA_MIPS_P8700_PAUSE_OPCODE));
}
