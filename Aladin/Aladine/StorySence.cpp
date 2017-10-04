#include "StorySence.h"
#include "MenuSence.h"
#include "SoundManager.h"

StorySence::StorySence(Game* game, int timeAni)
	:GameSence(game, timeAni)
{
	_allTime = 3000;
	_startTime = GetTickCount();
	_stopUpdate = false;
}

StorySence::~StorySence(void)
{
}

void StorySence::_Load()
{
}

// nhan 1 lan
void StorySence::_OnKeyDown(int keyCode){
}

void StorySence::_OnKeyUp(int keyCode)
{
}

// nhan va giu
void StorySence::_ProcessInput()
{
}

void StorySence::_UpdateRender(int t)
{
	
}

