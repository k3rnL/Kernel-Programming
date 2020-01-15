#ifndef _IDT_
#define _IDT_

#include <k/types.h>
#include "io.h"

#define IDTBASE  0x800		/* addr. physique ou doit resider la IDT */
#define IDTSIZE  0xFF		/* nombre max. de descripteurs dans la table */
#define INTGATE  0x8E00		/* utilise pour gerer les interruptions */

/* struct idtdesc */
/* { */
/*   unsigned short offset0_15: 16; */
/*   unsigned short select: 16; */
/*   unsigned short type: 16; */
/*   unsigned short offset16_31: 16; */
/* } __attribute__ ((packed)); */

/* struct idt_r { */
/*   u16 limit; */
/*   u32 base; */
/* } __attribute__ ((packed)); */

#endif