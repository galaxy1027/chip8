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
    uint8_t x = chip8->v[(chip8->opcode & 0x0F00) >> 8];
    uint8_t y = chip8->v[(chip8->opcode & 0x00F0) >> 4];
    uint8_t n = chip8->opcode & 0x000F;
    chip8->v[0xF] = 0;

    for (int row = 0; row < n; ++row) {
        uint8_t spriteByte = chip8->ram[chip8->i + row];
        for (int col = 0; col < 8; ++col) {
            uint8_t spritePixel = spriteByte & (0x80 >> col);
            uint8_t* screenPixel = &chip8->display[x][y];
            if (spritePixel) {
                if (*screenPixel == 0xFF) {
                    chip8->v[0xF] = 1;
                }
                chip8->display[x][y] ^= 0xFF;
            }
        }
    }
}