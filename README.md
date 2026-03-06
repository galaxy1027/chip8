# Chip8 Emulator

Credit to:
https://tobiasvl.github.io/blog/write-a-chip-8-emulator/
https://en.wikipedia.org/wiki/CHIP-8
for explanations on how the chip8 interpreter works.

https://austinmorlan.com/posts/chip8_emulator/
for implementations of drawing opcodes.

Raylib was used for handling graphics and controls, as well as the build template.
https://github.com/raysan5/raylib

## Building
ALL Operating Systems require a C compiler and CMake.

Linux will require packages for:

ALSA for audio, Mesa for OpenGL accelerated graphics and X11 for windowing system.

### Build Steps

#### Linux / MacOS
1. cd into the repo ``$ cd chip8``
2. ``$ cmake .``
3. ``$ make``

## Running
There are some test ROMS included. You can either run those or your own chip8 roms.

Syntax for using the emulator: `$ ./chip8 <scale-factor> <path-to-rom>`
