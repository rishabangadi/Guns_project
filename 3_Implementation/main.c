#include "header_files.h"

extern game_t game;
extern plane_t plane;

int main(void)
{
    memset(&game, 0, sizeof(game_t));
    initSDL();
    
    plane.x = 100;
    plane.y = 100;
    plane.texture = loadTexture("Images/plane1.png");

    atexit(cleanup);
    int i = 0;
    while (1)
    {
        prepareScene();
        check_input();
        render_texture(plane.texture, plane.x, plane.y);i++;
        presentScene();
        SDL_Delay(16);
    }
    return 0;
}
