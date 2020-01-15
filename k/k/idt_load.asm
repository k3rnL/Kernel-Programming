global idt_load
extern idtr, isr_default_int

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
		jmp %2
		restore_register
%endmacro

%macro ISR_ERRCODE 2
	[GLOBAL interrupt_%1]
	interrup_%1:
		cli
		push %1
		save_register
		jmp %2
		restore_regiter
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
