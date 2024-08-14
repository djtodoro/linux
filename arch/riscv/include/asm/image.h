/* SPDX-License-Identifier: GPL-2.0 */

#ifndef _ASM_RISCV_IMAGE_H
#define _ASM_RISCV_IMAGE_H

#define RISCV_IMAGE_MAGIC	"RISCV\0\0\0"
#define RISCV_IMAGE_MAGIC2	"RSC\x05"

#define RISCV_IMAGE_FLAG_BE_SHIFT	0
#define RISCV_IMAGE_FLAG_BE_MASK	0x1

#define RISCV_IMAGE_FLAG_LE		0
#define RISCV_IMAGE_FLAG_BE		1

#ifdef CONFIG_CPU_BIG_ENDIAN
#define __HEAD_FLAG_BE		RISCV_IMAGE_FLAG_BE
#else
#define __HEAD_FLAG_BE		RISCV_IMAGE_FLAG_LE
#endif

#define __HEAD_FLAG(field)	(__HEAD_FLAG_##field << \
				RISCV_IMAGE_FLAG_##field##_SHIFT)

#define __HEAD_FLAGS		(__HEAD_FLAG(BE))

#define RISCV_HEADER_VERSION_MAJOR 0
#define RISCV_HEADER_VERSION_MINOR 2

#define RISCV_HEADER_VERSION (RISCV_HEADER_VERSION_MAJOR << 16 | \
			      RISCV_HEADER_VERSION_MINOR)

#ifdef CONFIG_RISCV_M_MODE
/* Image load offset (0MB) from start of RAM for M-mode */
#define RISCV_LOAD_OFFSET 0x000000
#else
#if __riscv_xlen == 64
/* Image load offset(2MB) from start of RAM */
#define RISCV_LOAD_OFFSET 0x200000
#else
/* Image load offset(4MB) from start of RAM */
#define RISCV_LOAD_OFFSET 0x400000
#endif /* __riscv_xlen == 64 */
#endif /* CONFIG_RISCV_M_MODE */

/*
 * There aren't any ELF relocations we can use to endian-swap values known only
 * at link time (e.g. the subtraction of two symbol addresses), so we must get
 * the linker to endian-swap certain values before emitting them.
 *
 * Based on arch/arm64/kernel/image.h
 */

#ifdef CONFIG_CPU_BIG_ENDIAN
#define DATA_LE64(data)				        \
    ((((data) & 0x00000000000000ff) << 56) |     \
     (((data) & 0x000000000000ff00) << 40) |     \
     (((data) & 0x0000000000ff0000) << 24) |     \
     (((data) & 0x00000000ff000000) << 8)  |     \
     (((data) & 0x000000ff00000000) >> 8)  |     \
     (((data) & 0x0000ff0000000000) >> 24) |     \
     (((data) & 0x00ff000000000000) >> 40) |     \
     (((data) & 0xff00000000000000) >> 56))
#else
#define DATA_LE64(data) (data)
#endif /* CONFIG_CPU_BIG_ENDIAN */

#define DEFINE_IMAGE_LE64(sym, data)				\
	sym = DATA_LE64(data)

#define HEAD_SYMBOLS						\
	DEFINE_IMAGE_LE64(_kernel_offset_le, RISCV_LOAD_OFFSET);	\
	DEFINE_IMAGE_LE64(_kernel_size_le, _end - _text);	\
	DEFINE_IMAGE_LE64(_kernel_flags_le, __HEAD_FLAGS);

#if !defined(__ASSEMBLY__) && !defined(LINKER_SCRIPT)
/**
 * struct riscv_image_header - riscv kernel image header
 * @code0:		Executable code
 * @code1:		Executable code
 * @text_offset:	Image load offset (little endian)
 * @image_size:		Effective Image size (little endian)
 * @flags:		kernel flags (little endian)
 * @version:		version
 * @res1:		reserved
 * @res2:		reserved
 * @magic:		Magic number (RISC-V specific; deprecated)
 * @magic2:		Magic number 2 (to match the ARM64 'magic' field pos)
 * @res3:		reserved (will be used for PE COFF offset)
 *
 * The intention is for this header format to be shared between multiple
 * architectures to avoid a proliferation of image header formats.
 */

struct riscv_image_header {
	u32 code0;
	u32 code1;
	u64 text_offset;
	u64 image_size;
	u64 flags;
	u32 version;
	u32 res1;
	u64 res2;
	u64 magic;
	u32 magic2;
	u32 res3;
};
#endif /* !defined(__ASSEMBLY__) && !defined(LINKER_SCRIPT) */
#endif /* _ASM_RISCV_IMAGE_H */
