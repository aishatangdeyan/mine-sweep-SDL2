/*
* �汾 c++11
* ����SDL_2��ɨ����Ϸ
* ����̨�Ǻ�̨����(�رտ���̨��Ҫ�Լ�ͨ��ide�ر�)
* �ߴ�����Ҫ�Լ�����
*/
#include "SGame.h"
#include <SDL_gui.h>

int main(int argc, char* argv[])
{
	SGame* game = getGame();
	if (!game_init(game, u8"ɨ��", 350, 350))
	{
		SDL_Log("game init fail");
		return -1;
	}
	GUI_Init(game->renderer);
	while (game_isRunnig(game))
	{
		game_frameStart(game);
		GUI_Prepare();

		//�����¼�
		if (game_handleEvents(game))
			GUI_Update(&game->event);
		//��Ⱦ
		game_render(game);
		//�����¼�
		game_update(game);

		GUI_Finish();
		game_frameEnd(game);
	}
	GUI_Clean();
	game_clean(game);
	return 0;
}