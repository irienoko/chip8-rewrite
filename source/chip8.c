#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "chip8.h"


//default fonts i stole
const unsigned char font[80] =
{
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5s
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

void LoadRomFile(char *filepath, chip8_emu *emu_state)
{
	printf("loading %s into memory \n", filepath);

	//open file
	FILE *f = fopen(filepath, "rb");
	//check if file is not provided and exit
	if(f == NULL){printf("ERROR: Failed to open %s quitting\n", filepath); exit(1);}

	//retrive file info
	struct stat st;
	stat(filepath, &st);
	size_t fsize = st.st_size;

	//check if file size in bytes is larger that allocated memory array exculding reserved
	if(fsize > sizeof(emu_state->memory) - 0x200){printf("file too large daddy... owo \n"); exit(1);}
	
	//load file into memory starting at 0x200
	size_t bytes_read = fread(emu_state->memory + 0x200, 1, sizeof(emu_state->memory) - 0x200, f);

	if(ferror(f))
	{
		printf("ERROR: Read process was unsuccessful or incomplete. somethings gone to shit \n");
		printf("should prob rerun LoadRomFile function \n");

	}

	//check if the bytes that have been read are eual to the size of the file
	if(bytes_read != fsize)
	{
		printf("ERROR: Failed to load file into memory. should prob rerun LoadRomFile function \n");
		exit(1);
	}

	
	fclose(f);
}

