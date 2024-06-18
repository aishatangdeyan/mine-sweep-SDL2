#ifndef MINESWEEP_H_
#define	MINESWEEP_H_
#include<SDL.h>

#define ROWS 10
#define COLS 10
#define TITE_SIZE 35
typedef enum State
{
	StNormal,
	GameOver,
	GameWin
}State;
typedef struct MineSweep
{
	int map[ROWS][COLS];
	SDL_Texture* texs[12];

	State state;
}MineSweep;

MineSweep* GetMineSweep();
void ms_clean(MineSweep* pthis);
void ms_render(MineSweep* pthis);
void ms_update(MineSweep* pthis);

void ms_openBlackEmpty(MineSweep* pthis,int x,int y);
void ms_judge(MineSweep* pthis,int r,int c);
void ms_show(MineSweep* pthis);
#endif // !MINESWEEP_H_
