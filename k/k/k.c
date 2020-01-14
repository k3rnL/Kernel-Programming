/*
 * Copyright (c) LSE
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY LSE AS IS AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL LSE BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <k/kstd.h>
#include <k/types.h>
#include <stdio.h>
#include "io.h"
#include "multiboot.h"


void init_serial();
void init_gdt();
void init_idt();
void k_main(unsigned long magic, multiboot_info_t *info);

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

void k_main(unsigned long magic, multiboot_info_t *info)
{
  (void)magic;
  (void)info;

  printf("kernel : loading serial...\n");
  init_serial();
  printf("kernel : serial loaded!\n");

  printf("kernel : loading new gdt...\n");
  init_gdt();
  printf("kernel : new gdt loaded!\n");

  printf("kern : loading idt...\n");
  init_idt();
  init_pic();
  printf("kernel : idt loaded!\n");

  
  while(1);
}


//ISR_ERROR 8- 10>15 17
