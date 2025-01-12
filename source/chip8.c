#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

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

void ParseOPCodes(chip8_emu *emu_state)
{
	unsigned short op = emu_state->memory[emu_state->PC] << 8 | emu_state->memory[emu_state->PC + 1];

	int x = (op & 0x0F00) >> 8;
	int y = (op & 0x00F0) >> 4;

	// take the op value eg. 10F0 & it with F000 so we can ignore the other 12 bits leaving use with 1000
	switch(op & 0xF000)
	{
		case 0x0000:
		{
			switch(op & 0x0FFF)
			{
				case 0x00E0: {printf("clear display \n"); memset(emu_state->display, 0, sizeof(emu_state->display)); emu_state->PC +=2; } break;
				case 0x00EE: {printf("return from subroutine \n"); emu_state->SP -=2; emu_state->PC = emu_state->stack[emu_state->PC]; emu_state->PC +=2;} break;
			}
		}break;

		case 0x1000:
		{
			
		}break;

		case 0x2000:
		{
			
		}break;

		case 0x3000:
		{
			
		}break;

		case 0x4000:
		{
			
		}break;

		case 0x5000:
		{
			
		}break;

		case 0x6000:
		{
			
		}break;

		case 0x7000:
		{
			
		}break;

		case 0x8000:
		{
			switch (op & 0x000F)
			{
				case 0x0:
				{
					
				}break;

				case 0x1:
				{
					
				}break;

				case 0x2:
				{
					
				}break;

				case 0x3:
				{
					
				}break;

				case 0x4:
				{
					
				}break;

				case 0x5:
				{
					
				}break;

				case 0x6:
				{
					
				}break;

				case 0x7:
				{
					
				}break;

				case 0xE:
				{
					
				}break;
			}
		}break;

		case 0x9000:
		{
			
		}break;

		case 0xA000:
		{
			
		}break;

		case 0xB000:
		{
			
		}break;

		case 0xC000:
		{
			
		}break;

		case 0xD000:
		{
			
		}break;

		case 0xE000:
		{
			switch (op & 0x00FF)
			{
				case 0x9E:
				{
					
				}break;

				case 0xA1:
				{
					
				}break;
			}
		}break;

		case 0xF000:
		{
			switch (op & 0x00FF)
			{
				case 0x07:
				{
					
				}break;

				case 0x0A:
				{
					
				}break;

				case 0x15:
				{
					
				}break;

				case 0x18:
				{
					
				}break;

				case 0x1E:
				{
					
				}break;

				case 0x29:
				{
					
				}break;

				case 0x33:
				{
					
				}break;

				case 0x55:
				{
					
				}break;

				case 0x65:
				{
					
				}break;
			}
		}
	}
}

