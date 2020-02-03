#include "include/io.h"

#define DLL 0x3F8
#define DLM 0x3F8+1
#define LCR 0x3F8+3
#define IER 0x3F8+1
#define FCR 0x3F8+2
#define THR 0x3F8

void init_serial()
{
  int _LCR = inb(0x3F8 + 3);
  outb(LCR, _LCR | (1<<7));	//met le bit a 1
  outb(DLL, 1);			//initialisation de DLL
  outb(DLM, 0);			//initialization DLM
  outb(LCR, _LCR & (~(1 << 7))); // DLAB=0

  outb(LCR, _LCR | (0<<2));	//no parity
  int _FCR = inb(FCR);
  _FCR = _FCR | (1<<1);
  _FCR = _FCR | (1<<2);
  _FCR = _FCR | (1<<6);
  _FCR = _FCR | (1<<7);
  outb(FCR, _FCR);

  int _IER = inb(0x3f8+1);
  outb(IER, _IER | (1<<1));
}

int write(const char *buf, size_t count)
{
  unsigned int i = -1;
  while (++i != count)
    {
      outb(THR, buf[i]);
    }
  outb(THR, '\r');
  outb(THR, '\n');
  return 1;
}

//qemu -serial -stdio
