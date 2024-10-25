#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "raylib.h"
#include "chip8.h"
#include "instruction.h"

int main(int argc, char* argv[]) {

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <scale> <ROM>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const float fps = 500.0;

    SetTargetFPS(fps);
    
    int scale = atoi(argv[1]);
    char* const filename = argv[2];

    InitWindow(64*scale, 32*scale, "Chip-8");

    Chip8* chip8 = (Chip8*)malloc(sizeof(Chip8));
    init(chip8);
    loadRom(chip8, argv[2]);
    bool quit = false;

    while (!quit) {
        if (WindowShouldClose()) {
            quit = true;
        }
        processInput(chip8);
        fetch(chip8);
        updateScreen(chip8, scale);
    }

    CloseWindow();
    free(chip8);
    return 0;
}

void loadRom(Chip8* chip8, const char* filename) {
    FILE* ROM = fopen(filename, "r");

    if (ROM == NULL) {
        fprintf(stderr, "ERROR: Invalid ROM path.\n");
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
    chip8->sp = 0;
    for (int i = 0; i < 80; ++i) {
        chip8->ram[0x50 + i] = font[i];
    }
}

void fetch(Chip8* chip8) {
    uint16_t op = ((chip8->ram[chip8->pc]) << 8) | chip8->ram[chip8->pc+1];
    chip8->pc += 2;
    chip8->opcode = op;
    execute(chip8);
}

void execute(Chip8* chip8) {
    uint16_t opcode = chip8->opcode;
    //printf("%x\n", opcode);
    uint8_t n4 = opcode & 0x000F;
    uint8_t n3 = (opcode >> 4) & 0x000F;
    uint8_t n2 = (opcode >> 8) & 0x000F;
    uint8_t n1 = (opcode >> 12) & 0x000F;

    switch(n1) {
        case 0x0:
            switch (n4) {
                case 0x0:
                    clearScreen(chip8);
                    break;
                case 0xE:
                    returnSubroutine(chip8);
                    break;
            }
            break;
        case 0x1:
            jump(chip8);
            break;
        case 0x2:
            callSubroutine(chip8);
            break;
        case 0x3:
            skipVxByte(chip8);
            break;
        case 0x4:
            skipNotVxByte(chip8);
            break;
        case 0x5:
            skipVxVy(chip8);
            break;
        case 0x6:
            set(chip8);
            break;
        case 0x7:
            add(chip8);
            break;
        case 0x8:
            switch(n4) {
                case 0x0:
                    setXY(chip8);
                    break;
                case 0x1:
                    OR(chip8);
                    break;
                case 0x2:
                    AND(chip8);
                    break;
                case 0x3:
                    XOR(chip8);
                    break;
                case 0x4:
                    addXY(chip8);
                    break;
                case 0x5:
                    subXY(chip8);
                    break;
                case 0x6:
                    shiftRight(chip8);
                    break;
                case 0x7:
                    subYX(chip8);
                    break;
                case 0xE:
                    shiftLeft(chip8);
                    break;
            }
            break;
        case 0x9:
            skipNotVxVy(chip8);
            break;
        case 0xA:
            setIndex(chip8);
            break;
        case 0xB:
            jumpOffset(chip8);
            break;
        case 0xC:
            randomNumber(chip8);
            break;
        case 0xD:
            draw(chip8);
            break;
        case 0xE:
            switch (n4) {
                case 0xE:
                    skipIfKey(chip8);
                    break;
                case 0x1:
                    skipIfNotKey(chip8);
                    break;
            }
        case 0xF:
            switch(n4) {
                case 0x3:
                    decimalConversion(chip8);
                    break;
                case 0x5:
                    if (n3 == 5) {
                        storeReg(chip8);
                    }
                    else if (n3 == 6) {
                        loadReg(chip8);
                    }
                    else if (n3 == 1) {
                        setDelay(chip8);
                    }
                    break;
                case 0x7:
                    vxTimer(chip8);
                    break;
                case 0x8:
                    setSound(chip8);
                    break;
                case 0x9:
                    fontCharacter(chip8);
                    break;
                case 0xA:
                    getKey(chip8);
                    break;
                case 0xE:
                    addToIndex(chip8);
            }
            break;
    }
}

void updateScreen(Chip8* chip8, int scale) {
    BeginDrawing();
    ClearBackground(BLACK);
    for (int x = 0; x < 64; ++x) {
        for (int y = 0; y < 32; ++y) {
            if (chip8->display[x][y]) {
                DrawRectangle(x*scale, y*scale, scale, scale, RAYWHITE);
            }
        }
    }
    EndDrawing();
}

void processInput(Chip8* chip8) {
    chip8->keyPressed = 0;
    for (int i = 0; i < 16; ++i) {
        if (IsKeyPressed(keys[i])) {
            chip8->keypad[i] = 1;
            chip8->keyPressed = keys[i];
            printf("%d", chip8->keyPressed);
        }
        else if (IsKeyReleased(keys[i])) {
            chip8->keypad[i] = 0;
        }
    }
}
