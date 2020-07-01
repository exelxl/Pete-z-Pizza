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
#define IMG_BG "gfx/bgI.png"

static void logic(void);
static void draw(void);
static void drawHud(void);

void initStage(void)
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;

	memset(&stage, 0, sizeof(Stage));

	stage.entityTail = &stage.entityHead;

	initEntities();

	initPlayer();

	initMap();
}

static void logic(void)
{
	doPlayer();

	doEntities();

	doCamera();
}

static void draw(void)
{
	// background image ingame loading
	SDL_Surface* bgimgIG = IMG_Load(IMG_BG); // load image as surface
	SDL_Texture* bgimgIGcon = SDL_CreateTextureFromSurface(app.renderer, bgimgIG); // convert image(surface) to texture
	SDL_FreeSurface(bgimgIG); // free the surface

	// rect to put background image into
	SDL_Rect bgI;

	bgI.x = 0; // x coordinate
	bgI.y = 0; // y coordinate
	bgI.w = 1280; // rectangle width
	bgI.h = 720; // rectangle height

	SDL_RenderCopy(app.renderer, bgimgIGcon, NULL, &bgI); // copy image into the rectangle
	SDL_DestroyTexture(bgimgIGcon); // destroy texture

	drawMap();

	drawEntities();

	drawHud();
}

static void drawHud(void)
{
	SDL_Rect r;

	r.x = 0;
	r.y = 0;
	r.w = SCREEN_WIDTH;
	r.h = 35;

	//rectangle for health icon
	SDL_Rect hRec;

	hRec.x = 920;
	hRec.y = 0;
	hRec.w = 30;
	hRec.h = 30;

	// rectangle for enemies icon
	SDL_Rect aiRec;

	aiRec.x = 20;
	aiRec.y = 3;
	aiRec.w = 30;
	aiRec.h = 30;

	// rectangle top 
	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_BLEND); // alpha blend mode
	SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 196); // alpha property
	SDL_RenderFillRect(app.renderer, &r); // fill rectangle

	// health HUD
	SDL_Surface* heartimg = IMG_Load("gfx/health_heart.png"); // load image as surface
	SDL_Texture* himgcon = SDL_CreateTextureFromSurface(app.renderer, heartimg); // convert image to texture
	SDL_FreeSurface(heartimg); // free the surface

	// enemies HUD
	SDL_Surface* aiIMG = IMG_Load("gfx/ai01.png"); // load image as surface
	SDL_Texture* aiIMGcon = SDL_CreateTextureFromSurface(app.renderer, aiIMG); // convert image to texture
	SDL_FreeSurface(aiIMG); // free the surface

	// copy the health heart icon to hRec rectangle
	SDL_RenderCopy(app.renderer, himgcon, NULL, &hRec);
	SDL_DestroyTexture(himgcon); //destroy texture

	// copy the enemies icon to aiRec rectangle
	SDL_RenderCopy(app.renderer, aiIMGcon, NULL, &aiRec);
	SDL_DestroyTexture(aiIMGcon); //destroy texture

	// drawing text on screen
	drawText(SCREEN_WIDTH - 5, 5, 255, 255, 255, TEXT_RIGHT, "PIZZA %d/%d", stage.pizzaFound, stage.pizzaTotal); // pizza collected/total text
	drawText(SCREEN_WIDTH - 200, 5, 255, 255, 255, TEXT_RIGHT, "%d/%d", player->health, player->tHealth); // health current/total text
	drawText(250, 5, 255, 255, 255, TEXT_RIGHT, "ENEMIES %d/%d", stage.aiKilled, stage.aiTotal); // enemies killed/total text
}
