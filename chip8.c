#include <stdio.h>
#include <stdlib.h>
#include "chip8.h"
#include "instruction.h"

void loadRom(Chip8* chip8, const char* filename) {
    FILE* ROM = fopen(filename, "r");

    if (ROM == NULL) {
        fprintf(stderr, "ERROR: Invalid file path.\n");
        exit(EXIT_FAILURE);
    }

    fseek(ROM, 0, SEEK_END);
    int fileSize = ftell(ROM);
    rewind(ROM);

    if (fileSize > 3584) {
        fprintf(stderr, "ERROR: ROM is too large.\n");
        exit(EXIT_FAILURE);
    }

    uint8_t buf[fileSize];
    fread(buf, sizeof(uint8_t), fileSize, ROM);

    for (int i = 0; i < fileSize; ++i) {
        chip8->ram[0x200 + i] = buf[i];
    }
}

void init(Chip8* chip8) {
    chip8->pc = 0x200;

    for (int i = 0; i < 80; ++i) {
        chip8->ram[0x50 + i] = font[i];
    }
    
}

void fetch(Chip8* chip8) {
    uint16_t op = ((chip8->ram[chip8->pc]) << 2) | chip8->ram[chip8->pc+1];
    chip8->pc += 2;
    chip8->opcode = op;
}

void execute(Chip8* chip8) {

}