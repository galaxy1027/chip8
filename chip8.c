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
    uint8_t n4 = chip8->opcode & 0x000F;
    uint8_t n3 = (chip8->opcode >> 4) & 0x000F;
    uint8_t n2 = (chip8->opcode >> 8) & 0x000F;
    uint8_t n1 = (chip8->opcode >> 12) & 0x000F;

    switch(n1) {
        case 0x0:
            switch (n4) {
                case 0x0:
                    clearScreen(chip8);
                    break;
                case 0xE:
                    break;
            }
            break;

        case 0x1:
            jump(chip8);
            break;

        case 0x6:
            set(chip8);
            break;
        
        case 0x7:
            add(chip8);
            break;

        case 0xA:
            set(chip8);
            break;

        case 0xD:
            draw(chip8);
            break;
    }
}