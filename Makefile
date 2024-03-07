HEADERS = chip8.h instruction.h
OBJECTS = chip8.o instruction.o
CFLAGS = -lraylib -lm
default: chip8

%.o: %.c $(HEADERS)
	cc -c $< -o $@

chip8: $(OBJECTS)
	cc  $(CFLAGS) $(OBJECTS) -o $@

clean:
	-rm -f $(OBJECTS)
	-rm -f program
