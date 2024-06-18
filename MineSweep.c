#include "MineSweep.h"
#include "SGame.h"
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define randNumber(min_,max_) rand() % (max_) + (min_)
void ms_openBlackEmpty(MineSweep* pthis, int x, int y);
void ms_judge(MineSweep* pthis, int r, int c);
MineSweep* GetMineSweep()
{
	static MineSweep ms;

	srand(time(NULL));
	//设置雷
	//并在设置雷的时候进行加减
	for (size_t i = 0; i < 10;)
	{
		int r = randNumber(0, ROWS);
		int c = randNumber(0, COLS);
		if (ms.map[r][c] != -1)
		{
			ms.map[r][c] = -1;
			for (int j = r - 1; j <= r + 1; j++)
			{
				for (int k = c - 1; k <= c + 1; k++)
				{
					if (j >= 0 && j < ROWS && k >= 0 && k < COLS && ms.map[j][k] != -1)
					{
						ms.map[j][k]++;
					}
				}
			}
			i++;
		}
	}
	//加载图片
	char filename[128];
	for (size_t i = 0; i < 12; i++)
	{
		SDL_snprintf(filename, 128, "Resource/images/%d.jpg", i);
		ms.texs[i] = loadTexture(getGame()->renderer, filename);
	}
	//加密
	int* pmap = ms.map;
	for (size_t i = 0; i < ROWS * COLS; i++)
	{
		pmap[i] += 20;
	}
	ms.state = StNormal;
	return &ms;
}

void ms_clean(MineSweep* pthis)
{
}

void ms_render(MineSweep* pthis)
{
	for (size_t r = 0; r < ROWS; r++)
	{
		for (size_t c = 0; c < COLS; c++)
		{
			int x = c * TITE_SIZE;
			int y = r * TITE_SIZE;
			if (pthis->map[r][c] >= 0 && pthis->map[r][c] <= 8)
			{
				drawTexture(getGame()->renderer, x, y, pthis->texs[pthis->map[r][c]]);
			}
			else if (pthis->map[r][c] == -1)
			{
				drawTexture(getGame()->renderer, x, y, pthis->texs[9]);
			}
			else if (pthis->map[r][c] >= 19 && pthis->map[r][c] <= 28)
			{
				//drawTexture(getGame()->renderer, x, y, pthis->texs[10]);
				SDL_Rect rect = { x,y,TITE_SIZE,TITE_SIZE };
				SDL_RenderCopy(getGame()->renderer, pthis->texs[10], NULL, &rect);
			}
			else if (pthis->map[r][c] >= 39)
			{
				//drawTexture(getGame()->renderer, x, y, pthis->texs[10]);
				SDL_Rect rect = { x,y,TITE_SIZE,TITE_SIZE };
				SDL_RenderCopy(getGame()->renderer, pthis->texs[11], NULL, &rect);
			}
		}
	}
	if (pthis->state == GameOver)
	{
		SDL_Log("game over");
		getGame()->inRunning = false;
	}
	else if (pthis->state == GameWin)
	{
		SDL_Log("game win");
		getGame()->inRunning = false;
	}
}

void ms_update(MineSweep* pthis)
{
	SDL_Event* event = &getGame()->event;
	if (event->type == SDL_MOUSEBUTTONUP)
	{
		//确定坐标
		int c = event->button.x / TITE_SIZE;
		int r = event->button.y / TITE_SIZE;
		//按下左键
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			//先判断有没有翻起
			if (pthis->map[r][c] >= 19)
			{
				pthis->map[r][c] -= 20;
				ms_openBlackEmpty(pthis, r, c);
				ms_judge(pthis, r, c);
			}
		}
		//按下右键 标记
		else if (event->button.button == SDL_BUTTON_RIGHT)
		{
			//先判断有没有标记或者打开
			if (pthis->map[r][c] >= 19 && pthis->map[r][c] <= 28)
			{
				pthis->map[r][c] += 20;
			}
			else if (pthis->map[r][c] >= 39)
			{
				pthis->map[r][c] -= 20;
			}
		}
		ms_show(pthis);
	}
}

void ms_openBlackEmpty(MineSweep* pthis, int r, int c)
{
	if (pthis->map[r][c] != 0)
		return;
	//打开的是空白格子 就打开周围的格子
	printf("%d %d\n", r, c);
	for (int j = r - 1; j <= r + 1; j++)
	{
		for (int k = c - 1; k <= c + 1; k++)
		{
			if (j >= 0 && j < ROWS && k>=0 && k < COLS && pthis->map[j][k] >19)
			{
				pthis->map[j][k] -= 20;
				ms_openBlackEmpty(pthis, j, k);
			}
		}
	}
}

void ms_judge(MineSweep* pthis, int r, int c)
{
	//如果点击的是雷 直接结束
	if (pthis->map[r][c] == -1)
	{
		pthis->state = GameOver;
		return;
	}
	else
	{
		//判断点击了多少了非雷格子 这里也可以直接用一个变量 然后点击的时候进行判断
		int count = 0;
		for (size_t r = 0; r < ROWS; r++)
		{
			for (size_t c = 0; c < COLS; c++)
			{
				if (pthis->map[r][c] <= 8)
				{
					count++;
				}
			}
		}
		if (count == ROWS * COLS - 10)
		{
			pthis->state = GameWin;
		}

	}
}

void ms_show(MineSweep* pthis)
{
	for (size_t r = 0; r < ROWS; r++)
	{
		for (size_t c = 0; c < COLS; c++)
		{
			printf("%2d ", pthis->map[r][c]);
		}
		printf("\n");
	}
	printf("\n");
}
