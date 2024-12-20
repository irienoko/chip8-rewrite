#include <stdio.h>
#include <string.h>

#include <SDL2/SDL.h>

#include "chip8.h"

typedef unsigned char 		u8;
typedef unsigned short 		u16;
typedef unsigned int 		u32;
typedef unsigned long long	u64;

static struct 
{
	SDL_Window 	*window;
	SDL_Surface *window_surface;
	SDL_Surface	*canvas;
	u32 		*buffer;	
}basic_sdl;


void DrawPixel(int win_width, int win_height, int x, int y,u32 *buffer, u32 colour)
{
	if(x <= 0 && x < win_width && y >= 0 && y < win_height){buffer[y * win_width + x] = colour; }
}

void DrawFilledRect(int win_width, int win_height, int posx, int posy, int width, int height,u32 *buffer,u32 colour)
{  
    int xmin = posx, ymin = posy;
    int xmax = posx + width, ymax = posy + height;

    for(int hy=ymin;hy<=ymax;hy++)
    {
        for(int hx=xmin;hx<=xmax;hx++)
        {
            if(hx >= xmin && hx <= xmax && hy >= ymin && hy <= ymax)
            {
                DrawPixel(win_width, win_height, hx,hy,buffer, colour);
            }
        }
    }
}


int main(int argc, char **argv)
{
	chip8_emu emu_state;
	LoadRomFile(argv[1], &emu_state);
	

	if(SDL_Init(SDL_INIT_VIDEO) <0) {printf("failed to initlise SDL :["); exit(1);}
	basic_sdl.window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 512, 256, 0);

	basic_sdl.window_surface = SDL_GetWindowSurface(basic_sdl.window);

	basic_sdl.canvas = SDL_CreateRGBSurfaceWithFormat(0, 512, 256, 32,SDL_PIXELFORMAT_RGBA8888);

	basic_sdl.buffer = (u32*) basic_sdl.canvas->pixels;

	SDL_LockSurface(basic_sdl.canvas);

	DrawFilledRect(basic_sdl.canvas->w, basic_sdl.canvas->h, -30, 10, 20, 20,basic_sdl.buffer,0xFF0000FF);	

	SDL_UnlockSurface(basic_sdl.canvas);
	

	SDL_Event e;
	
	while(1)
	{
		while(SDL_PollEvent(&e))
		{
			if(e.type == SDL_QUIT) exit(0);
		}

		SDL_BlitSurface(basic_sdl.canvas, 0, basic_sdl.window_surface, 0);
		SDL_UpdateWindowSurface(basic_sdl.window);
	}

	SDL_Quit();
	return 0;
}
