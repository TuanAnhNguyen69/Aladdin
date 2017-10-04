#include "IntroSence.h"
#include "MenuSence.h"
#include "SoundManager.h"

IntroSence::IntroSence(Game* game, int timeAni)
	:GameSence(game, timeAni)
{
	_timeAni = 1000;
	_startTime = GetTickCount();
	_stopUpdate = false;
}

IntroSence::~IntroSence(void)
{
}

void IntroSence::_Load()
{
}

// nhan 1 lan
void IntroSence::_OnKeyDown(int keyCode){

}

void IntroSence::_OnKeyUp(int keyCode)
{
}

// nhan va giu
void IntroSence::_ProcessInput()
{
}

void IntroSence::_UpdateRender(int t)
{

}

