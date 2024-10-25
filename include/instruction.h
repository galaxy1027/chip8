#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "chip8.h"

void clearScreen(Chip8* chip8);

void returnSubroutine(Chip8* chip8);

void jump(Chip8* chip8);

void callSubroutine(Chip8* chip8);

void skipVxByte(Chip8* chip8);

void skipNotVxByte(Chip8* chip8);

void skipVxVy(Chip8* chip8);

void set(Chip8* chip8);

void add(Chip8* chip8);

void setXY(Chip8* chip8);

void OR(Chip8* chip8);

void AND(Chip8* chip8);

void XOR(Chip8* chip8);

void addXY(Chip8* chip8);

void subXY(Chip8* chip8);

void shiftRight(Chip8* chip8);

void subYX(Chip8* chip8);

void shiftLeft(Chip8* chip8);

void skipNotVxVy(Chip8* chip8);

void setIndex(Chip8* chip8);

void jumpOffset(Chip8* chip8);

void randomNumber(Chip8* chip8);

void draw(Chip8* chip8);

void skipIfKey(Chip8* chip8);

void skipIfNotKey(Chip8* chip8);

void vxTimer(Chip8* chip8);

void setDelay(Chip8* chip8);

void setSound(Chip8* chip8);

void getKey(Chip8* chip8);

void addToIndex(Chip8* chip8);

void fontCharacter(Chip8* chip8);

void decimalConversion(Chip8* chip8);

void storeReg(Chip8* chip8);

void loadReg(Chip8* chip8);

#endif