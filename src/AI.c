#include "common.h"

//void initPlayer(void);
static void tick(void);
static void touch(Entity* other);

// loading ai into the map
void initAI(char* line)
{
	Entity* ai;
	ai = malloc(sizeof(Entity));
	memset(ai, 0, sizeof(Entity));
	stage.entityTail->next = ai;
	stage.entityTail = ai;

	// setting the AI's pos
	sscanf(line, "%*s %f %f", &ai->sx, &ai->sy);

	// moving the AI to he map
	ai->x = ai->sx;
	ai->y = ai->sy;

	// charcter health
	ai->health = 5;

	// load AI texture
	ai->texture = loadTexture("gfx/ai01.png");

	// load the texture
	SDL_QueryTexture(ai->texture, NULL, NULL, &ai->w, &ai->h);
	ai->flags = EF_WEIGHTLESS + EF_PUSH; //flags for the character for it to behave a certain way

	// some vairables
	ai->tick = tick;
	ai->touch = touch;

	// total ai counter
	stage.aiTotal++;
}

// move left to right for motion
static void tick(void)
{ 
	self->value += (float)0.1;

	self->x += (float)sin(self->value);
}


static void touch(Entity* other)
{
	// if player health is more than 0 and is a player
	if (self->health > 0 && other == player)
	{
		if (app.keyboard[SDL_SCANCODE_F]) //when 5 is pressed kill enemy
		{
			if (player->health > 0)
			{
				self->health -= 5;
				stage.aiKilled++; // increase ai killed counter
			}
		}
	}
}