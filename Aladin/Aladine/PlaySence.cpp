#include "PlaySence.h"
#include "MenuSence.h"
#include "MapLoader.h"
#include "SoundManager.h"
#include "LoseGameSence.h"
#include "Writer.h"

PlaySence::PlaySence(Game* game, int timeAni)
	: GameSence(game, timeAni)
{
	SoundManager::GetInst()->PlayBgSound(SOUND_B_GAME1);
	_isExitting = false;
	IsVisiable = true;
}

PlaySence::~PlaySence(void)
{
	if(_QuadTree != NULL)
	{
		delete _QuadTree;
		_QuadTree = NULL;
	}

	if(_Camera != NULL)
	{
		delete _Camera;
		_Camera = NULL;
	}

	if(_aladdin != NULL)
	{
		delete _aladdin;
		_aladdin = NULL;
	}

	if(_BackgroundMng != NULL)
	{
		delete _BackgroundMng;
		_BackgroundMng = NULL;
	}
}

void PlaySence::_Load()
{
	
}

// nhan 1 lan
void PlaySence::_OnKeyDown(int keyCode)
{
	
}

//nhan 1 lan
void PlaySence::_OnKeyUp(int keyCode)
{
	
}

// nhan va giu
void PlaySence::_ProcessInput()
{

}

void PlaySence::_UpdateRender(int time)
{
	
#pragma endregion	
}

void PlaySence::LoadNewMap(void)
{
	//delete resource
	if(_QuadTree != NULL)
	{
		delete _QuadTree;
		_QuadTree = NULL;
	}

	if(_BackgroundMng != NULL)
	{
		delete _BackgroundMng;
		_BackgroundMng = NULL;
	}

	if(_Camera != NULL)
	{
		delete _Camera;
		_Camera = NULL;
	}
}

