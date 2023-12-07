#include "instruction.h"
#include "chip8.h"

void clearScreen(Chip8* chip8) {
    for (int x = 0; x < 64; ++x) {
        for (int y = 0; y < 32; ++y) {
            chip8->display[x][y] = 0;
        }
    }
}

void jump(Chip8* chip8) {
    chip8->pc = chip8->opcode & 0x0FFF;
}


void set(Chip8* chip8) {
    uint8_t reg = (chip8->opcode & 0x0F00) >> 8;
    chip8->v[reg] = chip8->opcode & 0x00FF;
}

void add(Chip8* chip8) {
    uint8_t reg = (chip8->opcode & 0x0F00) >> 8;
    chip8->v[reg] += chip8->opcode & 0x00FF;
}

void setIndex(Chip8* chip8) {
    chip8->i = chip8->opcode & 0x0FFF;
}

// DXYN
void draw(Chip8* chip8) {
    chip8->v[0xF] = 0;
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t y = (chip8->opcode & 0x00F0) >> 4;
    uint8_t height = chip8->opcode & 0x000F;
    uint8_t pixel = 0;

    for (uint16_t yLine = 0; yLine < height; yLine++) {
        pixel = chip8->ram[chip8->i + yLine];
        for (uint16_t xLine = 0; xLine < 8; xLine++) {
            if ((pixel & (0x80 >> xLine)) != 0) {

                if (chip8->display[(chip8->v[x] + xLine) % 64][(chip8->v[y] + yLine) % 32] == 1) {
                    chip8->v[0xF] = 1;
                }
                chip8->display[(chip8->v[x] + xLine) % 64][(chip8->v[y] + yLine) % 32] ^= 1;
            }
        }
    }
}