#include "LoseGameSence.h"
#include "MenuSence.h"
#include "SoundManager.h"
#include "Writer.h"

LoseGameSence::LoseGameSence(Game* game, int timeAni, PlaySence* playSence)
	:GameSence(game, timeAni)
{
	this->_playSence = playSence;
}

LoseGameSence::~LoseGameSence(void)
{
}

void LoseGameSence::_Load()
{

}

// nhan 1 lan
void LoseGameSence::_OnKeyDown(int keyCode){
	
}

void LoseGameSence::_OnKeyUp(int keyCode)
{
}

// nhan va giu
void LoseGameSence::_ProcessInput()
{
}

void LoseGameSence::_UpdateRender(int t)
{

}

