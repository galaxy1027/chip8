# Chip8 Emulator

Credit to:
https://tobiasvl.github.io/blog/write-a-chip-8-emulator/
https://en.wikipedia.org/wiki/CHIP-8
for explanations on how the chip8 interpreter works.

https://austinmorlan.com/posts/chip8_emulator/
for implementations of some opcodes.

Raylib was used for handling graphics and controls.


## Building
(Only works for MacOS / Linux)
1. Install raylib: https://github.com/raysan5/raylib
2. Clone into this repository and cd into it `$ cd chip8`
3. Run `$ make`

## Running
There are some test ROMS included. You can either run those or your own chip8 roms.

Syntax for using the emulator: `$ ./chip8 <scale-factor> <path-to-rom>`
