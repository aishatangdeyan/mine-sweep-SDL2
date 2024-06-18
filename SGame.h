#ifndef SGAME_H_
#define SGAME_H_
#include <stdbool.h>
#include <SDL.h>

//��ǰ����
typedef struct MineSweep MineSweep;
//��Ϸ�ṹ����
typedef struct SGame
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;

	MineSweep* ms;

	bool inRunning;
	float fps;
	uint32_t  startTime;
}SGame;
/**
 * ��ȡ��Ϸ����
 */
SGame* getGame();
/**
 * ��ʼ����Ϸ.
 * @param game ��ȡ��Ϸʵ��
 * @param title ��Ϸ���ڱ���
 * @param w	���ڵĿ��
 * @param h ���ڵĸ߶�
 */
bool game_init(SGame* game,char* title,int w,int h);
/**
 * ������Ϸ �ͷ���Դ.
 */
void game_clean(SGame* game);
/**
 * �ж���Ϸ�Ƿ���������
 */
bool game_isRunnig(SGame* game);
/*
 * ��Ϸ����.
 */
void game_quit(SGame* game);
/**
 * �����¼�
 */
bool game_handleEvents(SGame* game);
/**
 * ��Ⱦ
 */
void game_render(SGame* game);
/**
 * �����¼�
 */
void game_update(SGame* game);
/*
 * ����֡��.
 */
void game_setfps(SGame* game,int fps);
float game_fps(SGame* game);
void game_frameStart(SGame* game);
void game_frameEnd(SGame* game);
/**
 * ������������.
 */
SDL_Texture* loadTexture(SDL_Renderer* ren, const char* filename);
void drawTexture(SDL_Renderer* ren, int x, int y, SDL_Texture* tex);

#endif // !SGAME_H_	
