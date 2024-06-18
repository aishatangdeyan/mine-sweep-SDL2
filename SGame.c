#include "SGame.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_gui.h>
#include "MineSweep.h"

SGame* getGame()
{
	static SGame game;
	return &game;
}

bool game_init(SGame* game, char* title, int w, int h)
{
	if (SDL_Init(SDL_INIT_VIDEO) == 0 && IMG_Init(IMG_INIT_JPG) &&
		TTF_Init() == 0 && Mix_Init(MIX_INIT_MP3))
	{
		SDL_Log("init~");
		game->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
		if (game->window)
		{
			SDL_Log("create window~");
		}
		game->renderer = SDL_CreateRenderer(game->window, -1, 0);
		if (game->renderer)
		{
			SDL_Log("create renderer~");
		}
		game->inRunning = true;
	}
	else game->inRunning = false;
	game->fps = 1000 / 60;
	game->startTime = 0;
	game->ms = GetMineSweep();
	ms_show(game->ms);
	return game->inRunning;
}

void game_clean(SGame* game)
{
	if (game->renderer)
		SDL_DestroyRenderer(game->renderer);
	if (game->window)
		SDL_DestroyWindow(game->window);
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	SDL_Log("SDL Clean~");
}

bool game_isRunnig(SGame* game)
{
	return game->inRunning;
}

void game_quit(SGame* game)
{
	game->inRunning = false;
}

bool game_handleEvents(SGame* game)
{
	if (SDL_PollEvent(&game->event))
	{
		if (game->event.type == SDL_QUIT)
		{
			game_quit(game);
		}
		return true;
	}
	return false;
}

void game_render(SGame* game)
{
	SDL_SetRenderDrawColor(game->renderer, 230, 231, 232, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(game->renderer);
	//这部分实现具体的渲染
	ms_render(game->ms);
	//
	SDL_RenderPresent(game->renderer);
}

void game_update(SGame* game)
{
	ms_update(game->ms);
}

void game_setfps(SGame* game, int fps)
{
	game->fps = fps;
}

float game_fps(SGame* game)
{
	return game->fps;
}

void game_frameStart(SGame* game)
{
	game->startTime = SDL_GetTicks();
}

void game_frameEnd(SGame* game)
{
	int32_t remaining = SDL_GetTicks() - game->startTime;
	if (remaining < (int)game->fps)
	{
		SDL_Delay(game->fps - remaining);
	}
}

SDL_Texture* loadTexture(SDL_Renderer* ren, const char* filename)
{
	SDL_Surface* surface = IMG_Load(filename);
	if (!surface)
	{
		SDL_Log("SDL_LoadBMP failed, %s", SDL_GetError());
		return NULL;
	}
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, surface);
	if (!tex)
	{
		SDL_Log("SDL_CreateTextureFromSurface failed, %s", SDL_GetError());
		SDL_FreeSurface(surface);
		return NULL;
	}
	SDL_FreeSurface(surface);
	return tex;
}

void drawTexture(SDL_Renderer* ren, int x, int y, SDL_Texture* tex)
{
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	SDL_RenderCopy(ren, tex, NULL, &(SDL_Rect){x, y, w, h});
}
