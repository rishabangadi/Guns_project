#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <ctype.h>

#define WINDOW_WIDTH (1200)
#define WINDOW_HEIGHT (800)
#define MAX_KEYBOARD_KEYS (350)
#define PLAYER_SPEED 9
#define PLAYER_BULLET_SPEED 20

typedef struct Item Item;

void initSDL(void);
void cleanup(void);
void prepareScene(void);
void presentScene(void);
void check_input(void);
void doKeyUp(SDL_KeyboardEvent *event);
void doKeyDown(SDL_KeyboardEvent *event);
void render_texture(SDL_Texture *texture, int x, int y);
SDL_Texture *loadTexture(char *filename);
void initialise(void);
void initPlayer();
void logic(void);
void run_players(void);
void fireBullet(void);
void run_bullets(void);
void draw(void);
void drawPlayers(void);
void drawBullets(void);
void run_enemies(void);
void create_enemies(void);

typedef struct
{
	void (*logic)(void);
	void (*render_screen)(void);
} Execute_t;

typedef struct game
{
	SDL_Renderer *renderer;
	SDL_Window *window;
	Execute_t execute;
	int keyboard[MAX_KEYBOARD_KEYS];
} game_t;
game_t game;

typedef struct Item
{
	float x;
	float y;
	int w;
	int h;
	float dx;
	float dy;
	int health;
	int reload;
	SDL_Texture *texture;
	Item *next;
} Item;

typedef struct
{
	Item fighterHead, *fighterTail;
	Item bulletHead, *bulletTail;
} Stage;
Stage stage;