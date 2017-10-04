#include "ChangeMapSence.h"
#include "MenuSence.h"
#include "SoundManager.h"

ChangeMapSence::ChangeMapSence(Game* game, bool* isVisible, int curlevel, int timeAni)
	:GameSence(game, timeAni)
{
	this->IsVisiable = isVisible;
	*this->IsVisiable = false;
}

ChangeMapSence::~ChangeMapSence(void)
{
}

void ChangeMapSence::_Load()
{
	
}

void ChangeMapSence::_OnKeyDown(int keyCode)
{
	
}

void ChangeMapSence::_OnKeyUp(int keyCode)
{
}

void ChangeMapSence::_ProcessInput()
{
}

void ChangeMapSence::_UpdateRender(int time)
{

}

void ChangeMapSence::DrawLines(int x, int y, int nx, int ny)
{
	
}

