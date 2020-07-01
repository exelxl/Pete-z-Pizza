/*
Copyright (C) 2015-2018 Parallel Realities

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#include "common.h"
#define WIDTH_bg 1280 // background width
#define HEIGHT_bg 720 // background height
#define IMG_PATH "gfx/bg_IMG.png"

void initSDL(void)
{
	int rendererFlags, windowFlags;

	rendererFlags = SDL_RENDERER_ACCELERATED;
	SDL_Texture* bgimg = NULL; //assigning background image to a texture with value NULL
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	windowFlags = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	{
		printf("Couldn't initialize SDL Mixer\n");
		exit(1);
	}

	Mix_AllocateChannels(MAX_SND_CHANNELS);

	app.window = SDL_CreateWindow("Pete's Pizza Party 6", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);
	
	bgimg = IMG_LoadTexture(app.renderer, IMG_PATH); // load image as texture

	// rectangle for background
	SDL_Rect bgr;
	bgr.x = 0;
	bgr.y = 0;
	bgr.w = 1280;
	bgr.h = 720;

	// event handling
	while (1)
	{
		SDL_Event event;
		SDL_PollEvent(&event);

		// begin game
		if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_SPACE)
		{
			break;
		}

		// if statement to restart game
		if (event.type == SDL_KEYUP && event.key.keysym.sym == SDL_SCANCODE_R)
		{
			WinMain();
			break;
		}

		// quit game
		if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
		{
			exit(1);
		}

		// clear the rander
		SDL_RenderClear(app.renderer);
		// copy the texture to the rendering rect
		SDL_RenderCopy(app.renderer, bgimg, NULL, &bgr);
		// show game
		SDL_RenderPresent(app.renderer);
	}

	SDL_DestroyTexture(bgimg); // destroy texture
	SDL_ShowCursor(0); 
}

void initGame(void)
{
	initFonts();

	initSounds();

	loadMusic("music/one_0.mp3");

	playMusic(1);
}

void cleanup(void)
{
	SDL_DestroyRenderer(app.renderer);

	SDL_DestroyWindow(app.window);

	SDL_Quit();
}
