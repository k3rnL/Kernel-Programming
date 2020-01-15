global idt_load
extern idtr, isr_default_int, isr_gfp

idt_load:
	lidt [idtr]
	ret

%macro save_register 0
	pusha                    ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

	mov ax, ds               ; Lower 16-bits of eax = ds.
	push eax                 ; save the data segment descriptor

	mov ax, 0x10  ; load the kernel data segment descriptor
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
%endmacro	

%macro restore_register 0
	pop eax        ; reload the original data segment descriptor
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	popa                     ; Pops edi,esi,ebp...
	add esp, 8     ; Cleans up the pushed error code and pushed ISR number
	sti
	iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP
%endmacro	
	
%macro ISR_NOERRCODE 2  ; define a macro, taking interrupt code and handler
	[GLOBAL interrupt_%1]        ; %1 accesses the first parameter.
	interrupt_%1:
		cli
		push 0
		push %1
		save_register
		call %2
		restore_register
%endmacro

%macro ISR_ERRCODE 2
	[GLOBAL interrupt_%1]
	interrupt_%1:
		cli
		push %1
		save_register
		call %2
		restore_register
%endmacro

global isr_oui
isr_oui:
   cli
   push 0

   pusha                    ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

   mov ax, ds               ; Lower 16-bits of eax = ds.
   push eax                 ; save the data segment descriptor

   mov ax, 0x10  ; load the kernel data segment descriptor
   mov ds, ax
   mov es, ax
   mov fs, ax
   mov gs, ax

   call isr_default_int

   pop eax        ; reload the original data segment descriptor
   mov ds, ax
   mov es, ax
   mov fs, ax
   mov gs, ax

   popa                     ; Pops edi,esi,ebp...
   add esp, 8     ; Cleans up the pushed error code and pushed ISR number
   sti
   iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP

ISR_NOERRCODE 0, isr_default_int
ISR_NOERRCODE 1, isr_default_int
ISR_NOERRCODE 2, isr_default_int
ISR_NOERRCODE 3, isr_default_int
ISR_NOERRCODE 4, isr_default_int
ISR_NOERRCODE 5, isr_default_int
ISR_NOERRCODE 6, isr_default_int
ISR_NOERRCODE 7, isr_default_int
ISR_ERRCODE   8, isr_default_int
ISR_NOERRCODE 9, isr_default_int
ISR_ERRCODE   10, isr_default_int
ISR_ERRCODE   11, isr_default_int
ISR_ERRCODE   12, isr_default_int
ISR_ERRCODE   13, isr_gfp
ISR_ERRCODE   14, isr_default_int
ISR_NOERRCODE 15, isr_default_int
ISR_NOERRCODE 16, isr_default_int
ISR_NOERRCODE 17, isr_default_int
ISR_NOERRCODE 18, isr_default_int
ISR_NOERRCODE 19, isr_default_int
ISR_NOERRCODE 20, isr_default_int
ISR_NOERRCODE 21, isr_default_int
ISR_NOERRCODE 22, isr_default_int
ISR_NOERRCODE 23, isr_default_int
ISR_NOERRCODE 24, isr_default_int
ISR_NOERRCODE 25, isr_default_int
ISR_NOERRCODE 26, isr_default_int
ISR_NOERRCODE 27, isr_default_int
ISR_NOERRCODE 28, isr_default_int
ISR_NOERRCODE 29, isr_default_int
ISR_NOERRCODE 30, isr_default_int
ISR_NOERRCODE 31, isr_default_int
