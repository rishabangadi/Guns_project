#include "header_files.h"
extern game_t game;

int main(void)
{
    memset(&game, 0, sizeof(game_t));
    initSDL();
    atexit(cleanup);
    initialise();
    while (1)
    {
        prepareScene();
        check_input();
        game.execute.logic();
		game.execute.render_screen();
        presentScene();
        SDL_Delay(16);
    }
    return 0;
}
