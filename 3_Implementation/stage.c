#include "header_files.h"

extern game_t game;
extern Item plane;
extern Stage stage;
static Item *player;
static SDL_Texture *bulletTexture;


void initialise(void)
{
	game.execute.logic = logic;
	game.execute.render_screen = draw;
	memset(&stage, 0, sizeof(Stage));
	stage.fighterTail = &stage.fighterHead;
	stage.bulletTail = &stage.bulletHead;
	initPlayer();
	bulletTexture = loadTexture("Images/playerBullet.png");
}

void initPlayer()
{
	player = malloc(sizeof(Item));
	memset(player, 0, sizeof(Item));
	stage.fighterTail->next = player;
	stage.fighterTail = player;
	
	player->x = 100;
	player->y = 100;
	player->texture = loadTexture("Iamges/plane1.png");
	SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
}

void logic(void)
{
	run_players();
	run_bullets();
}

void run_players(void)
{
	player->dx = player->dy = 0;
	if (player->reload > 0)
	{
		player->reload--;
	}
	if (game.keyboard[SDL_SCANCODE_UP])
	{
		player->dy = -PLAYER_SPEED;
	}
	if (game.keyboard[SDL_SCANCODE_DOWN])
	{
		player->dy = PLAYER_SPEED;
	}
	if (game.keyboard[SDL_SCANCODE_LEFT])
	{
		player->dx = -PLAYER_SPEED;
	}
	if (game.keyboard[SDL_SCANCODE_RIGHT])
	{
		player->dx = PLAYER_SPEED;
	}
	if (game.keyboard[SDL_SCANCODE_LCTRL] && (player->reload == 0 ))
	{
		fireBullet();
	}
	player->x += player->dx;
	player->y += player->dy;
}