#ifndef CHIP_8
#define CHIP_8

typedef struct 
{
	//registers
	unsigned char V[16];
	unsigned short I;
	unsigned short PC;
	unsigned char SP;

	unsigned char delay_timer;
	unsigned char sound_timer;

	unsigned short stack[16];

	//general chip8 stuff
	unsigned char memory[4096];
	unsigned char keys[16];
	unsigned char display[2048];
}chip8_emu;

void LoadRomFile(char *filepath, chip8_emu *emu_state);

void ParseOPCodes(chip8_emu *emu_state);

#endif

