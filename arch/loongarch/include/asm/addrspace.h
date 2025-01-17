/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2020-2022 Loongson Technology Corporation Limited
 * Copyright (C) 2024 Jiaxun Yang <jiaxun.yang at flygoat.com>
 *
 * Derived from MIPS:
 * Copyright (C) 1996, 99 Ralf Baechle
 * Copyright (C) 2000, 2002  Maciej W. Rozycki
 * Copyright (C) 1990, 1999 by Silicon Graphics, Inc.
 */
#ifndef _ASM_ADDRSPACE_H
#define _ASM_ADDRSPACE_H

#include <linux/const.h>
#include <linux/sizes.h>

#include <asm/loongarch.h>

#ifndef IO_BASE
#define IO_BASE			CSR_DMW0_BASE
#endif

#ifndef CACHE_BASE
#define CACHE_BASE		CSR_DMW1_BASE
#endif

#ifndef UNCACHE_BASE
#define UNCACHE_BASE		CSR_DMW0_BASE
#endif

#define DMW_PABITS	48
#define TO_PHYS_MASK	((1ULL << DMW_PABITS) - 1)


#define TO_PHYS(x)		(		((x) & TO_PHYS_MASK))
#define TO_CACHE(x)		(CACHE_BASE   |	((x) & TO_PHYS_MASK))
#define TO_UNCACHE(x)		(UNCACHE_BASE |	((x) & TO_PHYS_MASK))

#ifdef __ASSEMBLY__
#define _ATYPE_
#define _ATYPE32_
#define _ATYPE64_
#else
#define _ATYPE_		__PTRDIFF_TYPE__
#define _ATYPE32_	int
#define _ATYPE64_	__s64
#endif

#ifdef CONFIG_64BIT
#define _CONST64_(x)	_UL(x)
#else
#define _CONST64_(x)	_ULL(x)
#endif

/*
 *  32/64-bit LoongArch address spaces
 */
#ifdef __ASSEMBLY__
#define _ACAST32_
#define _ACAST64_
#else
#define _ACAST32_		(_ATYPE_)(_ATYPE32_)	/* widen if necessary */
#define _ACAST64_		(_ATYPE64_)		/* do _not_ narrow */
#endif

#ifdef CONFIG_32BIT

#define UVRANGE			0x00000000
#define KPRANGE0		0x80000000
#define KPRANGE1		0xa0000000
#define KVRANGE			0xc0000000

#else

#define XUVRANGE		_CONST64_(0x0000000000000000)
#define XSPRANGE		_CONST64_(0x4000000000000000)
#define XKPRANGE		_CONST64_(0x8000000000000000)
#define XKVRANGE		_CONST64_(0xc000000000000000)

#endif

/*
 * Returns the physical address of a KPRANGEx / XKPRANGE address
 */
#define PHYSADDR(a)		((_ACAST64_(a)) & TO_PHYS_MASK)

#endif /* _ASM_ADDRSPACE_H */
