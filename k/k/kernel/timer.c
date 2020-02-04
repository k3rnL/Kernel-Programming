#include "timer.h"

static volatile u32 tick = 1;

static void timer_callback(/*registers_t regs*/)
{
    tick++;
    if (tick % 100 == 0) {
        printf("%d\n", tick / 100);
    }
}

void init_timer(u32 frequency)
{
   // Firstly, register our timer callback.
   register_interrupt_handler(IRQ0, &timer_callback);

   // The value we send to the PIT is the value to divide it's input clock
   // (1193180 Hz) by, to get our required frequency. Important to note is
   // that the divisor must be small enough to fit into 16-bits.
   u32 divisor = 1193182 / frequency;

   // Send the command byte.
   outb(0x43, 0x36);

   // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
   u8 l = (u8)(divisor & 0xff);
   u8 h = (u8)((divisor>>8) & 0xff);

   // Send the frequency divisor.
   outb(0x40, l);
   outb(0x40, h);
}
