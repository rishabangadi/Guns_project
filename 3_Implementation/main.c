#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

static void drawBackground(void);
static void doBackground(void);

#define WINDOW_WIDTH (1017)
#define WINDOW_HEIGHT (466)
int backgroundX;

// speed in pixels/second
#define SPEED (300)

int main(void)
{
    // attempt to initialize graphics and timer system
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("Hello, CS50!",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!win)
    {
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // create a renderer, which sets up the graphics hardware
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    SDL_Renderer *rend = SDL_CreateRenderer(win, -1, render_flags);
    if (!rend)
    {
        printf("error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    // load the image into memory using SDL_image library function
    SDL_Surface *surface = IMG_Load("Game_Background_142.png");
    if (!surface)
    {
        printf("error creating surface\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    // load the image data into the graphics hardware's memory
    SDL_Texture *tex = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    if (!tex)
    {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

  
    // set to 1 when window close button is pressed
    int close_requested = 0;

    // animation loop
    while (!close_requested)
    {
        // process events
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                close_requested = 1;
            }
        }

        if (--backgroundX < -WINDOW_WIDTH)
        {
            backgroundX = 0;
        }

        // clear the window
        SDL_RenderClear(rend);

        SDL_Rect dest;
        int x;

        for (x = backgroundX; x < WINDOW_WIDTH; x += WINDOW_WIDTH)
        {
            dest.x = x;
            dest.y = 0;
            dest.h = 515;
            dest.w = 1017;

            SDL_RenderCopy(rend, tex, NULL, &dest);
        }

        SDL_RenderPresent(rend);

        // wait 1/60th of a second
        SDL_Delay(1000 / 60);
    }

    // clean up resources before exiting
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
