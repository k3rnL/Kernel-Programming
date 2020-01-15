#ifndef _IDT_
#define _IDT_

#include <k/types.h>
#include "io.h"

#define IDTBASE  0x800		/* addr. physique ou doit resider la IDT */
#define IDTSIZE  0xFF		/* nombre max. de descripteurs dans la table */
#define INTGATE  0x8E00		/* utilise pour gerer les interruptions */

extern void interrupt_0();
extern void interrupt_1();
extern void interrupt_2();
extern void interrupt_3();
extern void interrupt_4();
extern void interrupt_5();
extern void interrupt_6();
extern void interrupt_7();
extern void interrupt_8();
extern void interrupt_9();
extern void interrupt_10();
extern void interrupt_11();
extern void interrupt_12();
extern void interrupt_13();
extern void interrupt_14();
extern void interrupt_15();
extern void interrupt_16();
extern void interrupt_17();
extern void interrupt_18();
extern void interrupt_19();
extern void interrupt_20();
extern void interrupt_21();
extern void interrupt_22();
extern void interrupt_23();
extern void interrupt_24();
extern void interrupt_25();
extern void interrupt_26();
extern void interrupt_27();
extern void interrupt_28();
extern void interrupt_29();
extern void interrupt_30();
extern void interrupt_31();

typedef struct registers
{
    u32 ds;                                      // Data segment selector
    u32 edi, esi, ebp, esp, ebx, edx, ecx, eax;  // Pushed by pusha.
    u32 int_no, err_code;                        // Interrupt number and error code (if applicable)
    u32 eip, cs, eflags, useresp, ss;            // Pushed by the processor automatically.
} registers_t;

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
