#include <stdlib.h>
#include "cpu.h"

void ld_bc_d16(u16 nn) {registers.bc = nn;}
void ld_bc_a() {registers.a = memory[registers.bc];}
void inc_bc() {registers.bc++;}
void inc_b() {registers.b++;}
void dec_b() {registers.b--;}
void ld_b_d8(u8 n) {registers.b = n;}
void rlca() {registers.a <<= 1;}

const struct instruction instructions[] = {
    [0x00] = {"NOP", 0, NULL},
    [0x01] = {"LD BC, d16", 2, ld_bc_d16},
    [0x02] = {"LD (BC), A", 0, ld_bc_a},
    [0x03] = {"INC BC", 0, inc_bc},
    [0x04] = {"INC B", 0, inc_b},
    [0x05] = {"DEC B", 0, dec_b},
    [0x06] = {"LD B, d8", 1, ld_bc_a},
    [0x07] = {"RLCA", 0, rlca},
    [0x08] = {"LD (BC), A", 0, ld_bc_a},
    [0x09] = {"LD (BC), A", 0, ld_bc_a},
    [0x0A] = {"LD (BC), A", 0, ld_bc_a},
};
