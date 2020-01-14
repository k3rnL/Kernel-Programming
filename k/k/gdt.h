#ifndef _GDT_
#define _GDT_

#include <k/types.h>

struct gdtdesc
{
  unsigned short limit: 16;
  unsigned short base: 16;
  unsigned char base16_23: 8;
  unsigned char type: 4;
  unsigned char s: 1;
  unsigned char dpl: 2;
  unsigned char p: 1;
  unsigned char lim16_19: 4;
  unsigned char avl: 1;
  unsigned char l: 1;
  unsigned char db: 1;
  unsigned char g: 1;
  unsigned char base24_31: 8;
} __attribute__ ((packed));

/* Registre GDTR */
struct gdt_r {
    u16 limit;
    u32 base;
} __attribute__ ((packed));

#endif
