#include "MenuSence.h"
#include "PlaySence.h"
#include "SoundManager.h"

int MenuSence::_curSelect = 0;

MenuSence::MenuSence(Game* game, int timeAni)
	:GameSence(game, timeAni)
{
}

MenuSence::~MenuSence(void)
{
}

void MenuSence::_Load()
{
	
}

// nhan 1 lan
void MenuSence::_OnKeyDown(int keyCode){

}

void MenuSence::_OnKeyUp(int keyCode)
{
}

// nhan va giu
void MenuSence::_ProcessInput()
{
}

void MenuSence::_UpdateRender(int t)
{

}

