# Chip8 Emulator

Credit to:
https://tobiasvl.github.io/blog/write-a-chip-8-emulator/
https://en.wikipedia.org/wiki/CHIP-8
for explanations on how the chip8 interpreter works.

https://austinmorlan.com/posts/chip8_emulator/
for implementations of some opcodes.

Raylib was used for handling graphics and controls, as well as the build template.
https://github.com/raysan5/raylib

## Building
ALL Operating Systems require a C compiler.

**GCC is recommended**

Windows will either require MinGW64 or Visual Studio to be installed.

Linux will require packages for:

ALSA for audio, Mesa for OpenGL accelerated graphics and X11 for windowing system.

### Build Steps
The raylib quickstart template is included. Reference https://github.com/raylib-extras/raylib-quickstart for details on how to run the build script for your specific OS.

The following steps do NOT apply to Windows Visual Studio, only MINGW64
1. Go into ``build`` directory ``$ cd build``
2. Run premake script:
   Windows: ``$ .\premake5.exe gmake2``
   MacOS: ``$ ./premake5.osx gmake2``
   Linux: ``$ ./premake5 gmake2``
4. Go back into root and run ``$ make``
5. Executable will be in ``bin/Debug/``

### Visual Studio
1. Run ``build-MinGW-W64.bat``
2. Run the generated ``.sln`` file
3. Develop the game in Visual Studio

## Running
There are some test ROMS included. You can either run those or your own chip8 roms.

Syntax for using the emulator: `$ ./chip8 <scale-factor> <path-to-rom>`
