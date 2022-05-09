#ifndef VGBE_CPU_H
#define VGBE_CPU_H
#include "util.h"

struct registers {
    union {
        struct {
            u8 a;
            u8 f;
        };
        u16 af; 
    };
    union {
        struct {
            u8 b;
            u8 c;
        };
        u16 bc;
    };
    union {
        struct {
            u8 d;
            u8 e;
        };
        u16 de;
    };
    union {
        struct {
            u8 h;
            u8 l;
        };
        u16 hl;
    };
    u16 sp; //stack pointer
    u16 pc; //program counter
} extern registers;

struct instruction {
    const char *disassembly;
    u8 arg_len;
    void (*execute); 
} extern const instructions[0xFF];

extern u8 memory[0xFFFF];


#endif
