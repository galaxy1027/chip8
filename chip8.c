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

    const float fps = 60.0;

    SetTargetFPS(60);
    
    int scale = atoi(argv[1]);
    char* const filename = argv[2];

    InitWindow(64*scale, 32*scale, "Chip-8");

    Chip8* chip8 = (Chip8*)malloc(sizeof(chip8));
    init(chip8);
    loadRom(chip8, argv[2]);
    bool quit = false;

    while (!quit) {
        fetch(chip8);
        execute(chip8);
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
    for (int i = 0; i < 80; ++i) {
        chip8->ram[0x50 + i] = font[i];
    }
}

void fetch(Chip8* chip8) {
    uint16_t op = ((chip8->ram[chip8->pc]) << 8) | chip8->ram[chip8->pc+1];
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
            setIndex(chip8);
            break;

        case 0xD:
            draw(chip8);
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