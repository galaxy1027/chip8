# Chip8 Emulator

Credit to:
https://tobiasvl.github.io/blog/write-a-chip-8-emulator/
https://en.wikipedia.org/wiki/CHIP-8
for explanations on how the chip8 interpreter works.

https://austinmorlan.com/posts/chip8_emulator/
for implementations of some opcodes.

Raylib was used for handling graphics and controls.


## Building
ALL Operating Systems require a C compiler

**GCC is recommended**

Linux will also require packages for:

ALSA for audio, Mesa for OpenGL accelerated graphics and X11 for windowing system.

### Build Steps
The raylib quickstart template is included. Reference https://github.com/raylib-extras/raylib-quickstart on how to run the build script for your specific OS.

## Running
There are some test ROMS included. You can either run those or your own chip8 roms.

Syntax for using the emulator: `$ ./chip8 <scale-factor> <path-to-rom>`
