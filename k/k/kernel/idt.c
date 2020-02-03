#include "io.h"
#include "idt.h"
#include "descriptor_tables.h"

#define IDT_ENTRIES 256

idt_entry_t idt_entries[IDT_ENTRIES];
idt_ptr_t   idt_ptr;

static void idt_set_gate(u8 num, u32 base, u16 sel, u8 flags)
{
    idt_entries[num].base_lo = base & 0xFFFF;
    idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

    idt_entries[num].sel     = sel;
    idt_entries[num].always0 = 0;
    // We must uncomment the OR below when we get to using user-mode.
    // It sets the interrupt gate's privilege level to 3.
    idt_entries[num].flags   = flags /* | 0x60 */;
}

void init_idt()
{
    idt_ptr.limit = sizeof(idt_entry_t) * 256 -1;
    idt_ptr.base  = (u32)&idt_entries;

    // Setup ISRs
    idt_set_gate(0,  (u32)isr0,  0x08, 0x8E);
    idt_set_gate(1,  (u32)isr1,  0x08, 0x8E);
    idt_set_gate(2,  (u32)isr2,  0x08, 0x8E);
    idt_set_gate(3,  (u32)isr3,  0x08, 0x8E);
    idt_set_gate(4,  (u32)isr4,  0x08, 0x8E);
    idt_set_gate(5,  (u32)isr5,  0x08, 0x8E);
    idt_set_gate(6,  (u32)isr6,  0x08, 0x8E);
    idt_set_gate(7,  (u32)isr7,  0x08, 0x8E);
    idt_set_gate(8,  (u32)isr8,  0x08, 0x8E);
    idt_set_gate(9,  (u32)isr9,  0x08, 0x8E);
    idt_set_gate(10, (u32)isr10, 0x08, 0x8E);
    idt_set_gate(11, (u32)isr11, 0x08, 0x8E);
    idt_set_gate(12, (u32)isr12, 0x08, 0x8E);
    idt_set_gate(13, (u32)isr13, 0x08, 0x8E);
    idt_set_gate(14, (u32)isr14, 0x08, 0x8E);
    idt_set_gate(15, (u32)isr15, 0x08, 0x8E);
    idt_set_gate(16, (u32)isr16, 0x08, 0x8E);
    idt_set_gate(17, (u32)isr17, 0x08, 0x8E);
    idt_set_gate(18, (u32)isr18, 0x08, 0x8E);
    idt_set_gate(19, (u32)isr19, 0x08, 0x8E);
    idt_set_gate(20, (u32)isr20, 0x08, 0x8E);
    idt_set_gate(21, (u32)isr21, 0x08, 0x8E);
    idt_set_gate(22, (u32)isr22, 0x08, 0x8E);
    idt_set_gate(23, (u32)isr23, 0x08, 0x8E);
    idt_set_gate(24, (u32)isr24, 0x08, 0x8E);
    idt_set_gate(25, (u32)isr25, 0x08, 0x8E);
    idt_set_gate(26, (u32)isr26, 0x08, 0x8E);
    idt_set_gate(27, (u32)isr27, 0x08, 0x8E);
    idt_set_gate(28, (u32)isr28, 0x08, 0x8E);
    idt_set_gate(29, (u32)isr29, 0x08, 0x8E);
    idt_set_gate(30, (u32)isr30, 0x08, 0x8E);
    idt_set_gate(31, (u32)isr31, 0x08, 0x8E);

    // Setup IRQs
    idt_set_gate(32, (u32)irq0, 0x08, 0x8E);
    idt_set_gate(33, (u32)irq1, 0x08, 0x8E);
    idt_set_gate(34, (u32)irq2, 0x08, 0x8E);
    idt_set_gate(35, (u32)irq3, 0x08, 0x8E);
    idt_set_gate(36, (u32)irq4, 0x08, 0x8E);
    idt_set_gate(37, (u32)irq5, 0x08, 0x8E);
    idt_set_gate(38, (u32)irq6, 0x08, 0x8E);
    idt_set_gate(39, (u32)irq7, 0x08, 0x8E);
    idt_set_gate(40, (u32)irq8, 0x08, 0x8E);
    idt_set_gate(41, (u32)irq9, 0x08, 0x8E);
    idt_set_gate(42, (u32)irq10, 0x08, 0x8E);
    idt_set_gate(43, (u32)irq11, 0x08, 0x8E);
    idt_set_gate(44, (u32)irq12, 0x08, 0x8E);
    idt_set_gate(45, (u32)irq13, 0x08, 0x8E);
    idt_set_gate(46, (u32)irq14, 0x08, 0x8E);
    idt_set_gate(47, (u32)irq15, 0x08, 0x8E);

    // Load IDT
    idt_flush((u32)&idt_ptr);

}

#include "../include/isr.h"

const char* exception_messages[] = {
        "Division By Zero Exception",
        "Debug Exception",
        "Non Maskable Interrupt Exception",
        "Breakpoint Exception",
        "Into Detected Overflow Exception",
        "Out of Bounds Exception",
        "Invalid Opcode Exception",
        "No Coprocessor Exception",
        "Double Fault Exception",
        "Coprocessor Segment Overrun Exception",
        "Bad TSS Exception",
        "Segment Not Present Exception",
        "Stack Fault Exception",
        "General Protection Fault Exception",
        "Page Fault Exception",
        "Unknown Interrupt Exception",
        "Coprocessor Fault Exception",
        "Alignment Check Exception (486+)",
        "Machine Check Exception (Pentium/586+)"
};

isr_t interrupt_handlers[256];

void register_interrupt_handler(u8 n, isr_t handler)
{
    interrupt_handlers[n] = handler;
}

void isr_handler(registers_t regs)
{
    printf("\n[Interrupt] code=%d", regs.int_no);
    if (regs.int_no < 20) {
        printf("\n[Interrupt] message=%s", exception_messages[regs.int_no]);
    }

    if (interrupt_handlers[regs.int_no] != 0) {
        isr_t handler = interrupt_handlers[regs.int_no];
        handler(regs);
    }
}

void irq_handler(registers_t regs)
{
    printf("\n[Interrupt] code=%d", regs.int_no);
    // Send an EOI (end of interrupt) signal to the PICs.
    // If this interrupt involved the slave.
    if (regs.int_no >= 40) {
        // Send reset signal to slave.
        outb(0xA0, 0x20);
    }
    // Send reset signal to master. (As well as slave, if necessary).
    outb(0x20, 0x20);

    if (interrupt_handlers[regs.int_no] != 0) {
        isr_t handler = interrupt_handlers[regs.int_no];
        handler(regs);
    }
}
