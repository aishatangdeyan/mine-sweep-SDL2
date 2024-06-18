#ifndef SGAME_H_
#define SGAME_H_
#include <stdbool.h>
#include <SDL.h>

//提前声明
typedef struct MineSweep MineSweep;
//游戏结构声明
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
 * 获取游戏单例
 */
SGame* getGame();
/**
 * 初始化游戏.
 * @param game 获取游戏实例
 * @param title 游戏窗口标题
 * @param w	窗口的宽度
 * @param h 窗口的高度
 */
bool game_init(SGame* game,char* title,int w,int h);
/**
 * 清理游戏 释放资源.
 */
void game_clean(SGame* game);
/**
 * 判断游戏是否正常运行
 */
bool game_isRunnig(SGame* game);
/*
 * 游戏结束.
 */
void game_quit(SGame* game);
/**
 * 处理事件
 */
bool game_handleEvents(SGame* game);
/**
 * 渲染
 */
void game_render(SGame* game);
/**
 * 更新事件
 */
void game_update(SGame* game);
/*
 * 控制帧率.
 */
void game_setfps(SGame* game,int fps);
float game_fps(SGame* game);
void game_frameStart(SGame* game);
void game_frameEnd(SGame* game);
/**
 * 其他帮助函数.
 */
SDL_Texture* loadTexture(SDL_Renderer* ren, const char* filename);
void drawTexture(SDL_Renderer* ren, int x, int y, SDL_Texture* tex);

#endif // !SGAME_H_	
