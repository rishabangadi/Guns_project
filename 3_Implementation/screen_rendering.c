#include "header_files.h"

void prepareScene(void)
{
	SDL_SetRenderDrawColor(game.renderer, 96, 128, 255, 255);
	SDL_RenderClear(game.renderer);
}

void presentScene(void)
{
	SDL_RenderPresent(game.renderer);
}

SDL_Texture* loadTexture(char *filename)
{
	SDL_Texture *texture;
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
	texture = IMG_LoadTexture(game.renderer, filename);
	return texture;
}

void render_texture(SDL_Texture *texture, int x, int y)
{
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	dest.w=114;dest.h=78;
	SDL_RenderCopy(game.renderer, texture, NULL, &dest);
}
