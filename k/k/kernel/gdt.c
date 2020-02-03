#include <stdio.h>
#include "../include/gdt.h"


static struct gdtdesc gdt[3] = {0};

void init_gdt_desc(u32 base, u32 limit, u32 dpl, u32 type, u32 nb)
{
  gdt[nb].base = base & 0xFFFF;

  gdt[nb].base16_23 = (base >> 16) & 0xFF;
  gdt[nb].base24_31 = (base >> 24) & 0xFF;

  gdt[nb].limit = limit;
  gdt[nb].dpl = dpl;
  gdt[nb].type = type;
  gdt[nb].avl = 0;
  gdt[nb].p = 1;
  gdt[nb].l = 0;
  gdt[nb].g = 1;
  gdt[nb].db = 1;
  gdt[nb].s = 1;
}

void init_gdt()
{
  //  init_gdt_desc(0x0, 0xFFFFF, 0, 11, 1);      /* code */
  //init_gdt_desc(0x0, 0xFFFFF, 0, 3, 2);      /* data */
init_gdt_desc(0x0, 0xFFFFFFFF, 0, 0x9a, 1);      /* code */
init_gdt_desc(0x0, 0xFFFFFFFF, 0, 0x92, 2);      /* data */
//init_gdt_desc(0xFFFF, 0xFFFFF, 0, 0x0D, 3);          /* stack */
  
  struct gdt_r gdtr;
  gdtr.base = gdt; /* gdt base address */
  gdtr.limit = sizeof(gdt) - 1; /* gdt size - 1 */

  asm volatile("lgdt %0\n"
  	       : /* no output */
  	       : "m" (gdtr)
  	       : "memory");


  asm volatile("movl %cr0, %eax \n \
                or 0x1, %eax \n \
	        movl %eax, %cr0");

  asm volatile("movw $0x10, %ax \n \
	       movw %ax, %ds \n \
	       movw %ax, %fs \n \
	       movw %ax, %gs \n \
               movw %ax, %es \n	\
	       movw %ax, %ss");
  
  asm volatile("ljmp $0x08, $1f \n \
	       1:");
}
