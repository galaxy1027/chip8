#include "chip8.h"
#include "instruction.h"

void clearScreen(Chip8* chip8) {
    int screensize = 64 * 32;
    for (int i = 0; i < screensize; ++i) {
        chip8->display[i] = 0;
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
    uint8_t x = chip8->v[(chip8->opcode & 0x0F00) >> 8] % 64;
    uint8_t y = chip8->v[(chip8->opcode & 0x00F0) >> 4] % 32;

    chip8->v[0xF] = 0;

    for (int row = 0; row < 32; ++row) {
        uint8_t spriteByte = chip8->ram[chip8->i + row];
        for (int col = 0; col < 8; ++col) {
            uint8_t spritePixel = spriteByte & (0x80 >> col);
            uint32_t* screenPixel = &(chip8->display[(y + row) * 64 + (x + col)]);

            if (spritePixel == 1) {
                if (*screenPixel == 0xFFFFFFFF) {
                    chip8->v[0xF] = 1;
                }
                *screenPixel = *screenPixel ^ 0xFFFFFFFF;
            }
        }
    }
}