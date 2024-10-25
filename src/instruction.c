#include <stdlib.h>
#include "instruction.h"
#include "chip8.h"

// 00E0
void clearScreen(Chip8* chip8) {
    for (int x = 0; x < 64; ++x) {
        for (int y = 0; y < 32; ++y) {
            chip8->display[x][y] = 0;
        }
    }
}

// 00EE
void returnSubroutine(Chip8* chip8) {
    --chip8->sp;
    chip8->pc = chip8->stack[(chip8->sp)];
    chip8->stack[chip8->sp] = 0;
}

// 1NNN
void jump(Chip8* chip8) {
    chip8->pc = chip8->opcode & 0x0FFF;
}

// 2NNN
void callSubroutine(Chip8* chip8) {
    chip8->stack[chip8->sp] = chip8->pc;
    chip8->pc = chip8->opcode & 0x0FFF;
    ++chip8->sp;
}

// 3XNN
void skipVxByte(Chip8* chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t byte = (chip8->opcode & 0x00FF);

    if (chip8->v[x] == byte) {
        chip8->pc += 2;
    }
}

// 4XNN
void skipNotVxByte(Chip8* chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t byte = (chip8->opcode & 0x00FF);

    if (chip8->v[x] != byte) {
        chip8->pc += 2;
    }
}

// 5XY0
void skipVxVy(Chip8* chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t y = (chip8->opcode & 0x00F0) >> 4;

    if (chip8->v[x] == chip8->v[y]) {
        chip8->pc += 2;
    }
}

// 6XNN
void set(Chip8* chip8) {
    uint8_t reg = (chip8->opcode & 0x0F00) >> 8;
    chip8->v[reg] = chip8->opcode & 0x00FF;
}

// 7XNN
void add(Chip8* chip8) {
    uint8_t reg = (chip8->opcode & 0x0F00) >> 8;
    chip8->v[reg] += chip8->opcode & 0x00FF;
}

// 8XY0
void setXY(Chip8* chip8){
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t y = (chip8->opcode & 0x00F0) >> 4;

    chip8->v[x] = chip8->v[y];
}

// 8XY1
void OR(Chip8* chip8){
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t y = (chip8->opcode & 0x00F0) >> 4;

    chip8->v[x] |= chip8->v[y];
    chip8->v[0xF] = 0;
}

// 8XY2
void AND(Chip8* chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t y = (chip8->opcode & 0x00F0) >> 4;

    chip8->v[x] &= chip8->v[y];
    chip8->v[0xF] = 0; 
}

// 8XY3
void XOR(Chip8* chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t y = (chip8->opcode & 0x00F0) >> 4;

    chip8->v[x] ^= chip8->v[y];    
    chip8->v[0xF] = 0;
}

// 8XY4
void addXY(Chip8* chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t y = (chip8->opcode & 0x00F0) >> 4;

    uint16_t sum = chip8->v[x] + chip8->v[y];
    chip8->v[x] = sum & 0xFF;
    if (sum > 255) {
        chip8->v[0xF] = 1;
    }
    else {
        chip8->v[0xF] = 0;
    }
}

// 8XY5
void subXY(Chip8* chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t y = (chip8->opcode & 0x00F0) >> 4;
    uint8_t VX = chip8->v[x];
    uint8_t VY = chip8->v[y];
    chip8->v[x] -= chip8->v[y];

    if (VX >= VY) {
        chip8->v[0xF] = 1;
    }
    else {
        chip8->v[0xF] = 0;
    }
    }

// 8XY6
void shiftRight(Chip8* chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t y = (chip8->opcode & 0x00F0) >> 4;
    chip8->v[x] = chip8->v[y];
    uint8_t VX = chip8->v[x];
    chip8->v[x] >>= 1;
    chip8->v[0xF] = VX & 0x01;
}

// 8XY7
void subYX(Chip8* chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t y = (chip8->opcode & 0x00F0) >> 4;
    uint8_t VX = chip8->v[x];
    uint8_t VY = chip8->v[y];
    chip8->v[x] = chip8->v[y] - chip8->v[x];

    if (chip8->v[y] > chip8->v[x]) {
        chip8->v[0xF] = 1;
    }
    else {
        chip8->v[0xF] = 0;
    }
}
// 8XYE
void shiftLeft(Chip8* chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t y = (chip8->opcode & 0x00F0) >> 4;
    chip8->v[x] = chip8->v[y];
    uint8_t VX = chip8->v[x];
    chip8->v[x] <<= 1;
    chip8->v[0xF] = (VX & 0x80) >> 7;

}

// 9XY0
void skipNotVxVy(Chip8* chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t y = (chip8->opcode & 0x00F0) >> 4;

    if (chip8->v[x] != chip8->v[y]) {
        chip8->pc += 2;
    }
}

// ANNN
void setIndex(Chip8* chip8) {
    chip8->i = chip8->opcode & 0x0FFF;
}

// BNNN
void jumpOffset(Chip8* chip8) {
    chip8->pc = (chip8->opcode & 0x0FFF) + chip8->v[0];
}

// CXNN
void randomNumber(Chip8* chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    chip8->v[x] = (chip8->opcode & 0x00FF) & rand();
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

// EX9E
void skipIfKey(Chip8* chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    if (chip8->keypad[chip8->v[x]] == 1) {
        chip8->pc += 2;
    }
}

// EXA1
void skipIfNotKey(Chip8* chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    if (chip8->keypad[chip8->v[x]] == 0) {
        chip8->pc += 2;
    }
}

// FX07
void vxTimer(Chip8* chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    chip8->v[x] = chip8->delayTimer;
}

// FX15
void setDelay(Chip8* chip8) {
    uint8_t x = (chip8->opcode * 0x0F00) >> 8;
    chip8->delayTimer = chip8->v[x];
}

// FX18
void setSound(Chip8* chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    chip8->soundTimer = chip8->v[x];
}

// FX0A
void getKey(Chip8* chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    if (chip8->keyPressed == 0) {
        chip8->pc -= 2;
    }
    else {
        chip8->v[x] = chip8->keyPressed;
    }
}

// FX1E
void addToIndex(Chip8* chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    chip8->i += chip8->v[x];
}

// FX29
void fontCharacter(Chip8* chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t digit = chip8->v[x];

    chip8->i = 0x50 + (5 * digit);

}

// FX33
void decimalConversion(Chip8* chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t num = chip8->v[x];
    chip8->ram[chip8->i+2] = num % 10;
    num /= 10;
    chip8->ram[chip8->i+1] = num % 10;
    num /= 10;
    chip8->ram[chip8->i] = num % 10;
}

// FX55
void storeReg(Chip8* chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    int n;
    for (n = 0; n <= x; ++n) {
        chip8->ram[chip8->i + n] = chip8->v[n];
    }
    chip8->i = n;
}

// FX65
void loadReg(Chip8* chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    for (int n = 0; n <= x; ++n) {
        chip8->v[n] = chip8->ram[chip8->i + n];
    }
}