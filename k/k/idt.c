#include "io.h"
#include "idt.h"

#define IDTBASE  0x800		/* addr. physique ou doit resider la IDT */
#define IDTSIZE  0xFF		/* nombre max. de descripteurs dans la table */

#define INTGATE  0x8E00		/* utilise pour gerer les interruptions */

extern void isr_oui();
extern void idt_load();
extern void interrupt_0();


void _asm_default_int(void);

/* #define ISR_NO_ERROR(N) \ */
/*   __asm__ volatile("\ */
/*        _asm_isr_"#N ": \n			   \ */
/*                 push $0 \n \ */
/*                 push $"#N " \n \ */
/*                 jmp _asm_default_int"); */
//ERROR


/* ISR_NO_ERROR(0); */
/* ISR_NO_ERROR(1); */
/* ISR_NO_ERROR(2); */
/* ISR_NO_ERROR(3); */
/* ISR_NO_ERROR(4); */
/* ISR_ERROR(8); */
/* ... */

struct idtdesc
{
	u16 offset0_15;
	u16 select;
	u16 type;
	u16 offset16_31;
} __attribute__((packed));

/* Registre IDTR */
struct idtr {
	u16 limite;
	u32 base;
} __attribute__ ((packed));

struct idtr idtr; /* Registre IDTR */
struct idtdesc idt[IDTSIZE]; /* Table de IDT */


/* struct idtdesc_t */
/* { */
/*   gs */
/*   fs */
/*   ... */
/*   ebx */
/*   eax */
/*   num_int */
/*   error */
/*   eip */
/*   cs */
/*   eflags */
/*   esp */
/*   ss */
/* } __attribute__((packed)); */

void generic_c_handler(void)
{
  printf("coucou\n");
  // if s->num_int < 32
  //	 exception
  //if  32 >= <= 32+15
  //	 IRQ
  //		EOI();
  //if  == 0x80
  //      SYSCALL
}

void isr_default_int(void)
{
	printf("interrupt\n");
}

void isr_clock_int(void)
{
}

void _asm_default_int()
{
  __asm__ volatile("call _asm_default_int_asm");




  /* asm volatile ("call generic_c_handler \n	\ */
  /* 	movb $0x20, %al \n \ */
  /* 	outb %al, $0x20 \n \ */
  /* 	iret"); */


      /* __asm__ volatile(;<save registers> \ */
      /* 		       pushl %esp	      \ */
      /* 		       call generic_c_handler \ */
      /* 		       add $4, %esp \ */
      /* 		       ;<restore registers> \ */
      /* 		       add $8, %esp \ */
      /* 		       iret) */

}

/* __asm__ volatile(" \ */
/* _asm_default_int: \n \ */
/* 	u16 offset0_15; */
/* 	u16 select; */
/* 	u16 type; */
/* 	u16 offset16_31; */
/* 	u16 offset0_15; */
/* 	u16 select; */
/* 	u16 type; */
/* 	u16 offset16_31; */
/*  push %eax \n		 \ */
/*  push %ebx */
/*  ... */
/*  push fs */
/*  push gs */
/*  push %esp */
/*  call generic_c_handler */
/*  ... */
/* 	        iret"); */



void init_idt_desc(u16 select, u32 function_ptr, u16 type, u32 nb)
{
  idt[nb].offset0_15 = (function_ptr & 0xffff);
  idt[nb].select = select;
  idt[nb].type = type;
  idt[nb].offset16_31 = (function_ptr & 0xffff0000) >> 16;
}

void memcpy(char *dest, char *src, size_t size)
{
  for (size_t i = 0 ; i < size ; i++) {
    *dest = *src;
    dest++;
    src++;
  }
}

void init_idt()
{
  printf("VOILA\n");
  /* Initialisation des descripteurs systeme par defaut */
  for (unsigned int i = 0; i < IDTSIZE; i++) 
    init_idt_desc(0x08, (u32) isr_oui, INTGATE, i);
  
  //init_idt_desc(0x08, (u32) _asm_irq_0, INTGATE, 33);
  /*
init_idt_desc(0x08, (u32) interrupt_1, INTGATE, 1);
init_idt_desc(0x08, (u32) interrupt_2, INTGATE, 2);
init_idt_desc(0x08, (u32) interrupt_3, INTGATE, 3);
init_idt_desc(0x08, (u32) interrupt_4, INTGATE, 4);
init_idt_desc(0x08, (u32) interrupt_5, INTGATE, 5);
init_idt_desc(0x08, (u32) interrupt_6, INTGATE, 6);
init_idt_desc(0x08, (u32) interrupt_7, INTGATE, 7);
init_idt_desc(0x08, (u32) interrupt_8, INTGATE, 8);
init_idt_desc(0x08, (u32) interrupt_9, INTGATE, 9);
init_idt_desc(0x08, (u32) interrupt_10, INTGATE, 10);
init_idt_desc(0x08, (u32) interrupt_11, INTGATE, 11);
init_idt_desc(0x08, (u32) interrupt_12, INTGATE, 12);
init_idt_desc(0x08, (u32) interrupt_13, INTGATE, 13);
init_idt_desc(0x08, (u32) interrupt_14, INTGATE, 14);
init_idt_desc(0x08, (u32) interrupt_15, INTGATE, 15);
init_idt_desc(0x08, (u32) interrupt_16, INTGATE, 16);
init_idt_desc(0x08, (u32) interrupt_17, INTGATE, 17);
init_idt_desc(0x08, (u32) interrupt_18, INTGATE, 18);
init_idt_desc(0x08, (u32) interrupt_19, INTGATE, 19);
init_idt_desc(0x08, (u32) interrupt_20, INTGATE, 20);
init_idt_desc(0x08, (u32) interrupt_21, INTGATE, 21);
init_idt_desc(0x08, (u32) interrupt_22, INTGATE, 22);
init_idt_desc(0x08, (u32) interrupt_23, INTGATE, 23);
init_idt_desc(0x08, (u32) interrupt_24, INTGATE, 24);
init_idt_desc(0x08, (u32) interrupt_25, INTGATE, 25);
init_idt_desc(0x08, (u32) interrupt_26, INTGATE, 26);
init_idt_desc(0x08, (u32) interrupt_27, INTGATE, 27);
init_idt_desc(0x08, (u32) interrupt_28, INTGATE, 28);
init_idt_desc(0x08, (u32) interrupt_29, INTGATE, 29);
init_idt_desc(0x08, (u32) interrupt_30, INTGATE, 30);
init_idt_desc(0x08, (u32) interrupt_31, INTGATE, 31);
init_idt_desc(0x08, (u32) interrupt_32, INTGATE, 32);
init_idt_desc(0x08, (u32) interrupt_33, INTGATE, 33);
init_idt_desc(0x08, (u32) interrupt_34, INTGATE, 34);
init_idt_desc(0x08, (u32) interrupt_35, INTGATE, 35);
init_idt_desc(0x08, (u32) interrupt_36, INTGATE, 36);
init_idt_desc(0x08, (u32) interrupt_37, INTGATE, 37);
init_idt_desc(0x08, (u32) interrupt_38, INTGATE, 38);
init_idt_desc(0x08, (u32) interrupt_39, INTGATE, 39);
init_idt_desc(0x08, (u32) interrupt_40, INTGATE, 40);
init_idt_desc(0x08, (u32) interrupt_41, INTGATE, 41);
init_idt_desc(0x08, (u32) interrupt_42, INTGATE, 42);
init_idt_desc(0x08, (u32) interrupt_43, INTGATE, 43);
init_idt_desc(0x08, (u32) interrupt_44, INTGATE, 44);
init_idt_desc(0x08, (u32) interrupt_45, INTGATE, 45);
init_idt_desc(0x08, (u32) interrupt_46, INTGATE, 46);
init_idt_desc(0x08, (u32) interrupt_47, INTGATE, 47);
init_idt_desc(0x08, (u32) interrupt_48, INTGATE, 48);
init_idt_desc(0x08, (u32) interrupt_49, INTGATE, 49);
init_idt_desc(0x08, (u32) interrupt_50, INTGATE, 50);
init_idt_desc(0x08, (u32) interrupt_51, INTGATE, 51);
init_idt_desc(0x08, (u32) interrupt_52, INTGATE, 52);
init_idt_desc(0x08, (u32) interrupt_53, INTGATE, 53);
init_idt_desc(0x08, (u32) interrupt_54, INTGATE, 54);
init_idt_desc(0x08, (u32) interrupt_55, INTGATE, 55);
init_idt_desc(0x08, (u32) interrupt_56, INTGATE, 56);
init_idt_desc(0x08, (u32) interrupt_57, INTGATE, 57);
init_idt_desc(0x08, (u32) interrupt_58, INTGATE, 58);
init_idt_desc(0x08, (u32) interrupt_59, INTGATE, 59);
init_idt_desc(0x08, (u32) interrupt_60, INTGATE, 60);
init_idt_desc(0x08, (u32) interrupt_61, INTGATE, 61);
init_idt_desc(0x08, (u32) interrupt_62, INTGATE, 62);
init_idt_desc(0x08, (u32) interrupt_63, INTGATE, 63);
init_idt_desc(0x08, (u32) interrupt_64, INTGATE, 64);
init_idt_desc(0x08, (u32) interrupt_65, INTGATE, 65);
init_idt_desc(0x08, (u32) interrupt_66, INTGATE, 66);
init_idt_desc(0x08, (u32) interrupt_67, INTGATE, 67);
init_idt_desc(0x08, (u32) interrupt_68, INTGATE, 68);
init_idt_desc(0x08, (u32) interrupt_69, INTGATE, 69);
init_idt_desc(0x08, (u32) interrupt_70, INTGATE, 70);
init_idt_desc(0x08, (u32) interrupt_71, INTGATE, 71);
init_idt_desc(0x08, (u32) interrupt_72, INTGATE, 72);
init_idt_desc(0x08, (u32) interrupt_73, INTGATE, 73);
init_idt_desc(0x08, (u32) interrupt_74, INTGATE, 74);
init_idt_desc(0x08, (u32) interrupt_75, INTGATE, 75);
init_idt_desc(0x08, (u32) interrupt_76, INTGATE, 76);
init_idt_desc(0x08, (u32) interrupt_77, INTGATE, 77);
init_idt_desc(0x08, (u32) interrupt_78, INTGATE, 78);
init_idt_desc(0x08, (u32) interrupt_79, INTGATE, 79);
init_idt_desc(0x08, (u32) interrupt_80, INTGATE, 80);
init_idt_desc(0x08, (u32) interrupt_81, INTGATE, 81);
init_idt_desc(0x08, (u32) interrupt_82, INTGATE, 82);
init_idt_desc(0x08, (u32) interrupt_83, INTGATE, 83);
init_idt_desc(0x08, (u32) interrupt_84, INTGATE, 84);
init_idt_desc(0x08, (u32) interrupt_85, INTGATE, 85);
init_idt_desc(0x08, (u32) interrupt_86, INTGATE, 86);
init_idt_desc(0x08, (u32) interrupt_87, INTGATE, 87);
init_idt_desc(0x08, (u32) interrupt_88, INTGATE, 88);
init_idt_desc(0x08, (u32) interrupt_89, INTGATE, 89);
init_idt_desc(0x08, (u32) interrupt_90, INTGATE, 90);
init_idt_desc(0x08, (u32) interrupt_91, INTGATE, 91);
init_idt_desc(0x08, (u32) interrupt_92, INTGATE, 92);
init_idt_desc(0x08, (u32) interrupt_93, INTGATE, 93);
init_idt_desc(0x08, (u32) interrupt_94, INTGATE, 94);
init_idt_desc(0x08, (u32) interrupt_95, INTGATE, 95);
init_idt_desc(0x08, (u32) interrupt_96, INTGATE, 96);
init_idt_desc(0x08, (u32) interrupt_97, INTGATE, 97);
init_idt_desc(0x08, (u32) interrupt_98, INTGATE, 98);
init_idt_desc(0x08, (u32) interrupt_99, INTGATE, 99);
init_idt_desc(0x08, (u32) interrupt_100, INTGATE, 100);
init_idt_desc(0x08, (u32) interrupt_101, INTGATE, 101);
init_idt_desc(0x08, (u32) interrupt_102, INTGATE, 102);
init_idt_desc(0x08, (u32) interrupt_103, INTGATE, 103);
init_idt_desc(0x08, (u32) interrupt_104, INTGATE, 104);
init_idt_desc(0x08, (u32) interrupt_105, INTGATE, 105);
init_idt_desc(0x08, (u32) interrupt_106, INTGATE, 106);
init_idt_desc(0x08, (u32) interrupt_107, INTGATE, 107);
init_idt_desc(0x08, (u32) interrupt_108, INTGATE, 108);
init_idt_desc(0x08, (u32) interrupt_109, INTGATE, 109);
init_idt_desc(0x08, (u32) interrupt_110, INTGATE, 110);
init_idt_desc(0x08, (u32) interrupt_111, INTGATE, 111);
init_idt_desc(0x08, (u32) interrupt_112, INTGATE, 112);
init_idt_desc(0x08, (u32) interrupt_113, INTGATE, 113);
init_idt_desc(0x08, (u32) interrupt_114, INTGATE, 114);
init_idt_desc(0x08, (u32) interrupt_115, INTGATE, 115);
init_idt_desc(0x08, (u32) interrupt_116, INTGATE, 116);
init_idt_desc(0x08, (u32) interrupt_117, INTGATE, 117);
init_idt_desc(0x08, (u32) interrupt_118, INTGATE, 118);
init_idt_desc(0x08, (u32) interrupt_119, INTGATE, 119);
init_idt_desc(0x08, (u32) interrupt_120, INTGATE, 120);
init_idt_desc(0x08, (u32) interrupt_121, INTGATE, 121);
init_idt_desc(0x08, (u32) interrupt_122, INTGATE, 122);
init_idt_desc(0x08, (u32) interrupt_123, INTGATE, 123);
init_idt_desc(0x08, (u32) interrupt_124, INTGATE, 124);
init_idt_desc(0x08, (u32) interrupt_125, INTGATE, 125);
init_idt_desc(0x08, (u32) interrupt_126, INTGATE, 126);
init_idt_desc(0x08, (u32) interrupt_127, INTGATE, 127);
init_idt_desc(0x08, (u32) interrupt_128, INTGATE, 128);
init_idt_desc(0x08, (u32) interrupt_129, INTGATE, 129);
init_idt_desc(0x08, (u32) interrupt_130, INTGATE, 130);
init_idt_desc(0x08, (u32) interrupt_131, INTGATE, 131);
init_idt_desc(0x08, (u32) interrupt_132, INTGATE, 132);
init_idt_desc(0x08, (u32) interrupt_133, INTGATE, 133);
init_idt_desc(0x08, (u32) interrupt_134, INTGATE, 134);
init_idt_desc(0x08, (u32) interrupt_135, INTGATE, 135);
init_idt_desc(0x08, (u32) interrupt_136, INTGATE, 136);
init_idt_desc(0x08, (u32) interrupt_137, INTGATE, 137);
init_idt_desc(0x08, (u32) interrupt_138, INTGATE, 138);
init_idt_desc(0x08, (u32) interrupt_139, INTGATE, 139);
init_idt_desc(0x08, (u32) interrupt_140, INTGATE, 140);
init_idt_desc(0x08, (u32) interrupt_141, INTGATE, 141);
init_idt_desc(0x08, (u32) interrupt_142, INTGATE, 142);
init_idt_desc(0x08, (u32) interrupt_143, INTGATE, 143);
init_idt_desc(0x08, (u32) interrupt_144, INTGATE, 144);
init_idt_desc(0x08, (u32) interrupt_145, INTGATE, 145);
init_idt_desc(0x08, (u32) interrupt_146, INTGATE, 146);
init_idt_desc(0x08, (u32) interrupt_147, INTGATE, 147);
init_idt_desc(0x08, (u32) interrupt_148, INTGATE, 148);
init_idt_desc(0x08, (u32) interrupt_149, INTGATE, 149);
init_idt_desc(0x08, (u32) interrupt_150, INTGATE, 150);
init_idt_desc(0x08, (u32) interrupt_151, INTGATE, 151);
init_idt_desc(0x08, (u32) interrupt_152, INTGATE, 152);
init_idt_desc(0x08, (u32) interrupt_153, INTGATE, 153);
init_idt_desc(0x08, (u32) interrupt_154, INTGATE, 154);
init_idt_desc(0x08, (u32) interrupt_155, INTGATE, 155);
init_idt_desc(0x08, (u32) interrupt_156, INTGATE, 156);
init_idt_desc(0x08, (u32) interrupt_157, INTGATE, 157);
init_idt_desc(0x08, (u32) interrupt_158, INTGATE, 158);
init_idt_desc(0x08, (u32) interrupt_159, INTGATE, 159);
init_idt_desc(0x08, (u32) interrupt_160, INTGATE, 160);
init_idt_desc(0x08, (u32) interrupt_161, INTGATE, 161);
init_idt_desc(0x08, (u32) interrupt_162, INTGATE, 162);
init_idt_desc(0x08, (u32) interrupt_163, INTGATE, 163);
init_idt_desc(0x08, (u32) interrupt_164, INTGATE, 164);
init_idt_desc(0x08, (u32) interrupt_165, INTGATE, 165);
init_idt_desc(0x08, (u32) interrupt_166, INTGATE, 166);
init_idt_desc(0x08, (u32) interrupt_167, INTGATE, 167);
init_idt_desc(0x08, (u32) interrupt_168, INTGATE, 168);
init_idt_desc(0x08, (u32) interrupt_169, INTGATE, 169);
init_idt_desc(0x08, (u32) interrupt_170, INTGATE, 170);
init_idt_desc(0x08, (u32) interrupt_171, INTGATE, 171);
init_idt_desc(0x08, (u32) interrupt_172, INTGATE, 172);
init_idt_desc(0x08, (u32) interrupt_173, INTGATE, 173);
init_idt_desc(0x08, (u32) interrupt_174, INTGATE, 174);
init_idt_desc(0x08, (u32) interrupt_175, INTGATE, 175);
init_idt_desc(0x08, (u32) interrupt_176, INTGATE, 176);
init_idt_desc(0x08, (u32) interrupt_177, INTGATE, 177);
init_idt_desc(0x08, (u32) interrupt_178, INTGATE, 178);
init_idt_desc(0x08, (u32) interrupt_179, INTGATE, 179);
init_idt_desc(0x08, (u32) interrupt_180, INTGATE, 180);
init_idt_desc(0x08, (u32) interrupt_181, INTGATE, 181);
init_idt_desc(0x08, (u32) interrupt_182, INTGATE, 182);
init_idt_desc(0x08, (u32) interrupt_183, INTGATE, 183);
init_idt_desc(0x08, (u32) interrupt_184, INTGATE, 184);
init_idt_desc(0x08, (u32) interrupt_185, INTGATE, 185);
init_idt_desc(0x08, (u32) interrupt_186, INTGATE, 186);
init_idt_desc(0x08, (u32) interrupt_187, INTGATE, 187);
init_idt_desc(0x08, (u32) interrupt_188, INTGATE, 188);
init_idt_desc(0x08, (u32) interrupt_189, INTGATE, 189);
init_idt_desc(0x08, (u32) interrupt_190, INTGATE, 190);
init_idt_desc(0x08, (u32) interrupt_191, INTGATE, 191);
init_idt_desc(0x08, (u32) interrupt_192, INTGATE, 192);
init_idt_desc(0x08, (u32) interrupt_193, INTGATE, 193);
init_idt_desc(0x08, (u32) interrupt_194, INTGATE, 194);
init_idt_desc(0x08, (u32) interrupt_195, INTGATE, 195);
init_idt_desc(0x08, (u32) interrupt_196, INTGATE, 196);
init_idt_desc(0x08, (u32) interrupt_197, INTGATE, 197);
init_idt_desc(0x08, (u32) interrupt_198, INTGATE, 198);
init_idt_desc(0x08, (u32) interrupt_199, INTGATE, 199);
init_idt_desc(0x08, (u32) interrupt_200, INTGATE, 200);
init_idt_desc(0x08, (u32) interrupt_201, INTGATE, 201);
init_idt_desc(0x08, (u32) interrupt_202, INTGATE, 202);
init_idt_desc(0x08, (u32) interrupt_203, INTGATE, 203);
init_idt_desc(0x08, (u32) interrupt_204, INTGATE, 204);
init_idt_desc(0x08, (u32) interrupt_205, INTGATE, 205);
init_idt_desc(0x08, (u32) interrupt_206, INTGATE, 206);
init_idt_desc(0x08, (u32) interrupt_207, INTGATE, 207);
init_idt_desc(0x08, (u32) interrupt_208, INTGATE, 208);
init_idt_desc(0x08, (u32) interrupt_209, INTGATE, 209);
init_idt_desc(0x08, (u32) interrupt_210, INTGATE, 210);
init_idt_desc(0x08, (u32) interrupt_211, INTGATE, 211);
init_idt_desc(0x08, (u32) interrupt_212, INTGATE, 212);
init_idt_desc(0x08, (u32) interrupt_213, INTGATE, 213);
init_idt_desc(0x08, (u32) interrupt_214, INTGATE, 214);
init_idt_desc(0x08, (u32) interrupt_215, INTGATE, 215);
init_idt_desc(0x08, (u32) interrupt_216, INTGATE, 216);
init_idt_desc(0x08, (u32) interrupt_217, INTGATE, 217);
init_idt_desc(0x08, (u32) interrupt_218, INTGATE, 218);
init_idt_desc(0x08, (u32) interrupt_219, INTGATE, 219);
init_idt_desc(0x08, (u32) interrupt_220, INTGATE, 220);
init_idt_desc(0x08, (u32) interrupt_221, INTGATE, 221);
init_idt_desc(0x08, (u32) interrupt_222, INTGATE, 222);
init_idt_desc(0x08, (u32) interrupt_223, INTGATE, 223);
init_idt_desc(0x08, (u32) interrupt_224, INTGATE, 224);
init_idt_desc(0x08, (u32) interrupt_225, INTGATE, 225);
init_idt_desc(0x08, (u32) interrupt_226, INTGATE, 226);
init_idt_desc(0x08, (u32) interrupt_227, INTGATE, 227);
init_idt_desc(0x08, (u32) interrupt_228, INTGATE, 228);
init_idt_desc(0x08, (u32) interrupt_229, INTGATE, 229);
init_idt_desc(0x08, (u32) interrupt_230, INTGATE, 230);
init_idt_desc(0x08, (u32) interrupt_231, INTGATE, 231);
init_idt_desc(0x08, (u32) interrupt_232, INTGATE, 232);
init_idt_desc(0x08, (u32) interrupt_233, INTGATE, 233);
init_idt_desc(0x08, (u32) interrupt_234, INTGATE, 234);
init_idt_desc(0x08, (u32) interrupt_235, INTGATE, 235);
init_idt_desc(0x08, (u32) interrupt_236, INTGATE, 236);
init_idt_desc(0x08, (u32) interrupt_237, INTGATE, 237);
init_idt_desc(0x08, (u32) interrupt_238, INTGATE, 238);
init_idt_desc(0x08, (u32) interrupt_239, INTGATE, 239);
init_idt_desc(0x08, (u32) interrupt_240, INTGATE, 240);
init_idt_desc(0x08, (u32) interrupt_241, INTGATE, 241);
init_idt_desc(0x08, (u32) interrupt_242, INTGATE, 242);
init_idt_desc(0x08, (u32) interrupt_243, INTGATE, 243);
init_idt_desc(0x08, (u32) interrupt_244, INTGATE, 244);
init_idt_desc(0x08, (u32) interrupt_245, INTGATE, 245);
init_idt_desc(0x08, (u32) interrupt_246, INTGATE, 246);
init_idt_desc(0x08, (u32) interrupt_247, INTGATE, 247);
init_idt_desc(0x08, (u32) interrupt_248, INTGATE, 248);
init_idt_desc(0x08, (u32) interrupt_249, INTGATE, 249);
init_idt_desc(0x08, (u32) interrupt_250, INTGATE, 250);
init_idt_desc(0x08, (u32) interrupt_251, INTGATE, 251);
init_idt_desc(0x08, (u32) interrupt_252, INTGATE, 252);
init_idt_desc(0x08, (u32) interrupt_253, INTGATE, 253);
init_idt_desc(0x08, (u32) interrupt_254, INTGATE, 254);
  */

  
/* Initialisation de la structure pour IDTR */
  idtr.limite = 255 - 1;
  idtr.base = (u32)idt;
  
 
  memcpy((char *) idtr.base, (char *) idt, idtr.limite);
  
  //  idt_load();

  asm volatile("lidt %0\n"
               : /* no output */
               : "m" (idtr) 
               : "memory");
  asm("sti"::);
  //	asm("lidtl (idtr)");
  
  
  
  
  
  /* struct idt_r idtr;		 */
  /* idtr.base = (u32)idt; /\* idt base address *\/ */
  /* idtr.limit = sizeof(idt) - 1; /\* idt size - 1 *\/ */
  /* __asm__ volatile("lidt %0\n" */
  /* 		   : /\* no output *\/ */
  /* 		   : "m" (idtr) */
  /* 		   : "memory"); */
}
