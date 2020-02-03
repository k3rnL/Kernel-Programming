//
// Created by k3rnL on 2/3/2020.
//

#include "io.h"
#include "descriptor_tables.h"

void init_pic(void)
{
    /* Initialisation de ICW1 */
    outb(0x20, 0x11);
    outb(0xA0, 0x11);

    /* Initialisation de ICW2 */
    outb(0x21, 0x20);	/* vecteur de depart = 32 */
    outb(0xA1, 0x70);	/* vecteur de depart = 96 */

    /* Initialisation de ICW3 */
    outb(0x21, 0x04);
    outb(0xA1, 0x02);

    /* Initialisation de ICW4 */
    outb(0x21, 0x01);
    outb(0xA1, 0x01);

    /* masquage des interruptions */
    outb(0x21, 0x0);
    outb(0xA1, 0x0);
}

void init_descriptor_tables() {
    printf("kernel : loading new gdt...\n");
    init_gdt();
    printf("kernel : new gdt loaded!\n");
    printf("kernel : loading idt...\n");
    init_pic();
    init_idt();
    printf("kernel : idt loaded!\n");
}
