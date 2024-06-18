/*
* 版本 c++11
* 基于SDL_2的扫雷游戏
* 控制台是后台处理(关闭控制台需要自己通过ide关闭)
* 尺寸宽度需要自己调整
*/
#include "SGame.h"
#include <SDL_gui.h>

int main(int argc, char* argv[])
{
	SGame* game = getGame();
	if (!game_init(game, u8"扫雷", 350, 350))
	{
		SDL_Log("game init fail");
		return -1;
	}
	GUI_Init(game->renderer);
	while (game_isRunnig(game))
	{
		game_frameStart(game);
		GUI_Prepare();

		//处理事件
		if (game_handleEvents(game))
			GUI_Update(&game->event);
		//渲染
		game_render(game);
		//更新事件
		game_update(game);

		GUI_Finish();
		game_frameEnd(game);
	}
	GUI_Clean();
	game_clean(game);
	return 0;
}