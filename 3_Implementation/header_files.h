#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include "SDL2/SDL_mixer.h"
#include <stdlib.h>
#include <ctype.h>

#define WINDOW_WIDTH (1200)
#define WINDOW_HEIGHT (800)
#define MAX_KEYBOARD_KEYS (350)
#define PLAYER_SPEED 4
#define PLAYER_BULLET_SPEED 20
#define SIDE_PLAYER 0
#define SIDE_ALIEN 1
#define ALIEN_BULLET_SPEED 8
#define MAX_STARS 500
#define MAX_SND_CHANNELS 8

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

typedef struct Item Item;
typedef struct Explosion Explosion;

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
void resetStage(void);
void doEnemies(void);
void fireAlienBullet(Item *e);
void clipPlayer(void);
void initStarfield(void);
void doBackground(void);
void doStarfield(void);
void doExplosions(void);
void addExplosions(int x, int y, int num);
void drawBackground(void);
void drawStarfield(void);
void drawExplosions(void);
void initSounds(void);
void loadSounds(void);
void loadMusic(char *filename);
void playMusic(int loop);
void playSound(int id, int channel);


int collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
int bulletHitFighter(Item *b);
void calcSlope(int x1, int y1, int x2, int y2, float *dx, float *dy);

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
	int side;
	SDL_Texture *texture;
	Item *next;
} Item;

typedef struct Explosion
{
	float x;
	float y;
	float dx;
	float dy;
	int r, g, b, a;
	Explosion *next;
}Explosion;

typedef struct
{
	Item fighterHead, *fighterTail;
	Item bulletHead, *bulletTail;
	Explosion explosionHead, *explosionTail;
} Stage;
Stage stage;

typedef struct
{
	int x;
	int y;
	int speed;
} Star;

enum
{
	CH_ANY = -1,
	CH_PLAYER,
	CH_ALIEN_FIRE
};

enum
{
	SND_PLAYER_FIRE,
	SND_ALIEN_FIRE,
	SND_PLAYER_DIE,
	SND_ALIEN_DIE,
	SND_MAX
};