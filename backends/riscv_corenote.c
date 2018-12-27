/* RISC-V specific core note handling.
   This file is part of elfutils.

   This file is free software; you can redistribute it and/or modify
   it under the terms of either

     * the GNU Lesser General Public License as published by the Free
       Software Foundation; either version 3 of the License, or (at
       your option) any later version

   or

     * the GNU General Public License as published by the Free
       Software Foundation; either version 2 of the License, or (at
       your option) any later version

   or both in parallel, as here.

   elfutils is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received copies of the GNU General Public License and
   the GNU Lesser General Public License along with this program.  If
   not, see <http://www.gnu.org/licenses/>.  */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <elf.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/time.h>

#define BACKEND	riscv_
#include "libebl_CPU.h"

#define	ULONG			uint64_t
#define PID_T			int32_t
#define	UID_T			uint32_t
#define	GID_T			uint32_t
#define ALIGN_ULONG		8
#define ALIGN_PID_T		4
#define ALIGN_UID_T		4
#define ALIGN_GID_T		4
#define TYPE_ULONG		ELF_T_XWORD
#define TYPE_PID_T		ELF_T_SWORD
#define TYPE_UID_T		ELF_T_WORD
#define TYPE_GID_T		ELF_T_WORD

static const Ebl_Register_Location prstatus_regs[] =
  {
    { .offset = 8, .regno = 1, .count = 31, .bits = 64 } /* x1..x31 */
  };
#define PRSTATUS_REGS_SIZE	(32 * 8)

#define PRSTATUS_REGSET_ITEMS						\
  {									\
    .name = "pc", .type = ELF_T_ADDR, .format = 'x',			\
    .offset = offsetof (struct EBLHOOK(prstatus), pr_reg[0]),		\
    .group = "register", .pc_register = true				\
  }

#include "linux-core-note.c"
