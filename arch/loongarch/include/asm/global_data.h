/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * (C) Copyright 2002
 * Wolfgang Denk, DENX Software Engineering, wd at denx.de.
 *
 * Copyright (C) 2024 Jiaxun Yang <jiaxun.yang at flygoat.com>
 */

#ifndef	__ASM_GBL_DATA_H
#define __ASM_GBL_DATA_H

#include <linux/types.h>
#include <asm/u-boot.h>
#include <compiler.h>

/* Architecture-specific global data */
struct arch_global_data {
#if CONFIG_IS_ENABLED(ACPI)
	ulong table_start;		/* Start address of ACPI tables */
	ulong table_end;		/* End address of ACPI tables */
	ulong table_start_high;		/* Start address of high ACPI tables */
	ulong table_end_high;		/* End address of high ACPI tables */
#endif
#ifdef CONFIG_SMBIOS
	ulong smbios_start;		/* Start address of SMBIOS table */
#endif
};

#include <asm-generic/global_data.h>

/* GD is stored in u0 (per CPU pointer) */
#define DECLARE_GLOBAL_DATA_PTR register gd_t *gd asm ("$r21")

static inline void set_gd(volatile gd_t *gd_ptr)
{
#ifdef CONFIG_64BIT
	asm volatile("ld.d $r21, %0\n" : : "m"(gd_ptr));
#else
	asm volatile("ld.w $r21, %0\n" : : "m"(gd_ptr));
#endif
}

#endif /* __ASM_GBL_DATA_H */
