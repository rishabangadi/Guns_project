#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>


#define WINDOW_WIDTH (1200)
#define WINDOW_HEIGHT (800)

void initSDL(void);
void cleanup(void);
void prepareScene(void);
void presentScene(void);
void check_input(void);
void render_texture(SDL_Texture *texture, int x, int y);
SDL_Texture* loadTexture(char *filename);


typedef struct game{
    SDL_Renderer *renderer;
	SDL_Window *window;
}game_t;
game_t game;

typedef struct plane{
	int x;
	int y;
	SDL_Texture *texture;
}plane_t;
plane_t plane;

