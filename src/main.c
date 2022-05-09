#include <stdlib.h>
#include <stdio.h>
#include "util.h"

u8 memory[0xFFFF];

struct rom_header {
    u8 entry_point[4];
    u8 logo[0x30];
    char title[16];
    u16 new_lic_code;
    u8 sgb_flag;
    u8 type;
    u8 rom_size;
    u8 ram_size;
    u8 dest_code;
    u8 lic_code;
    u8 version;
    u8 checksum;
    u8 global_checksum;
};

struct cart_context {
    char filename[1024];
    u32 rom_size;
    u8 *rom_data;
    struct rom_header *header;
} ctx;

const char *ROM_TYPES[] = {
    "ROM ONLY",
    "MBC1",
    "MBC1+RAM",
    "MBC1+RAM+BATTERY",
    "$04 ???",
    "MBC2",
    "MBC2+BATTERY",
    "$07 ???",
    "ROM+RAM",
    "ROM+RAM+BATTERY",
    "$0A ???",
    "MMM01",
    "MMM01+RAM",
    "MMM01+RAM+BATTERY",
    "$0E ???",
    "MBC3+TIMER+BATTERY",
    "MBC3+TIMER+RAM+BATTERY",
    "MBC3",
    "MBC3+RAM",
    "MBC3+RAM+BATTERY",
    "$14 ???",
    "$15 ???",
    "$16 ???",
    "$17 ???",
    "$18 ???",
    "MBC5",
    "MBC5+RAM",
    "MBC5+RAM+BATTERY",
    "MBC5+RUMBLE",
    "MBC5+RUMBLE+RAM",
    "MBC5+RUMBLE+RAM+BATTERY",
    "$1F ???",
    "MBC6",
    "$21 ???",
    "MBC7+SENSOR+RUMBLE+RAM+BATTERY",
};



bool load_rom(const char *name) {
    snprintf(ctx.filename, sizeof(ctx.filename), "%s", name);
    FILE *rom = fopen(name, "rb");
    
    if (rom == NULL) {
        fprintf(stderr, "could not open file: %s\n", name);
        return false;
    }

    printf("opened: %s\n", name);

    ctx.rom_data = memory;
    fread(ctx.rom_data, sizeof(u8), 0x7FFF, rom);
    fclose(rom);

    ctx.header = (struct rom_header *)(ctx.rom_data + 0x100); 
    ctx.header->title[15] = 0;

    printf("Cartridge loaded\n");
    printf("\tTitle:    %s\n", ctx.header->title);
    printf("\tType:     %s (%d)\n", ROM_TYPES[ctx.header->type], ctx.header->type);
    printf("\tROM size: %d\n", ctx.header->rom_size);
    printf("\tRAM size: %d\n", ctx.header->ram_size);
    printf("\tlogo:\n");
    for (int j = 1; j <= 3; j++) {
        printf("\t\t");
        for (int i = 0x10*(j-1); i < 0x10*j; i++)
            printf("%02X ", ctx.header->logo[i]); 
        printf("\n");
    }
    printf("\tRegion:   %d\n", ctx.header->dest_code);
    printf("\tVersion:  %d\n", ctx.header->version);
    printf("\tChecksum: %d\n", ctx.header->checksum);
    return true;
}


int main(int argc, char *argv[]) {
    load_rom(argv[1]);

    return 0;
}
