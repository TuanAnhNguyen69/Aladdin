#include "PlaySence.h"
#include "MenuSence.h"
#include "ZoomSence.h"
#include "MapLoader.h"
#include "Writer.h"
#include "SoundManager.h"
#include "LoseGameSence.h"

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
	//reset time
	_timeForLevel = TIME_FOR_LEVEL;

	_aladdin = new Aladdin(50, 50);
	_BackgroundMng = new BackgroundManager();

	CRECT mapRECT = CRECT(0, 0, GL_MapW, GL_MapH);
	_QuadTree = new QuadTree(mapRECT);

	MapLoader::TranslateMap(_QuadTree, _BackgroundMng, _aladdin, _timeForLevel);
	_BackgroundMng->Translate();
	_Camera = new Camera(CRECT(GL_WndSize));

	sprSmoke = new Sprite(ResourceMng::GetInst()->GetTexture("image/healthMeter.png"), 200);

}

void PlaySence::updateHealthMeter()
{
	int currentPos = -(_aladdin->_health - 8) * 2;
	sprSmoke->_start = currentPos;
	sprSmoke->_end = currentPos + 1;
	if (_aladdin->_health == 0)
		_aladdin->Dead();
}

// nhan 1 lan
void PlaySence::_OnKeyDown(int keyCode)
{
	if (keyCode == DIK_D) {
		_aladdin->Dead();
	}

	if (keyCode == DIK_H) {
		_aladdin->Hang();
	}

	if (keyCode == DIK_A) {
		_aladdin->Hit();
	}

	if (!_aladdin->getControlable())
		return;

	_aladdin->resetStandingTime();
	if (keyCode == DIK_RIGHT)
		_aladdin->TurnRight();
	else if (keyCode == DIK_LEFT)
		_aladdin->TurnLeft();
	else if (keyCode == DIK_J)
		_aladdin->Throw();
	else if (keyCode == DIK_L)
		_aladdin->Jump();
	else if (keyCode == DIK_K)
		_aladdin->Slash();
	else if (keyCode == DIK_D)
		_aladdin->Reborn();
}

//nhan 1 lan
void PlaySence::_OnKeyUp(int keyCode)
{
	if (!_aladdin->getControlable())
		return;
	if (_aladdin->isHanging() || _aladdin->isClimbing())
		return;
	if (keyCode == DIK_RIGHT || keyCode == DIK_LEFT)
		_aladdin->Stop();
}

// nhan va giu
void PlaySence::_ProcessInput()
{
	if (!_aladdin->getControlable())
		return;

	if (_game->IsKeyDown(DIK_RIGHT) || _game->IsKeyDown(DIK_LEFT)) {
		_aladdin->Move();
	} else if (_game->IsKeyDown(DIK_DOWN)) {
		if (_aladdin->isClimbing())
			_aladdin->Move(DIK_DOWN);
		_aladdin->Sit();
	} else if (_game->IsKeyDown(DIK_UP)) {
		if (_aladdin->isClimbing())
			_aladdin->Move(DIK_UP);
		_aladdin->LookUp();
	} else {
		if (_aladdin->isHanging())
			_aladdin->Hang();
		else if (_aladdin->isClimbing())
			_aladdin->Climb();
		else
			_aladdin->Stand();
	}
}

void PlaySence::_UpdateRender(int time)
{
	_aladdin->Update(time);
	updateHealthMeter();
	sprSmoke->Update(time);
	if(! IsVisiable)
		return;

#pragma region Begin Render
	D3DXMATRIX mat;
	float x = _Camera->GetRect().Left;
	float y = _Camera->GetRect().Top;
	D3DXVECTOR2 trans(- x, - y);
	D3DXMatrixTransformation2D(&mat, NULL, 0.0f, NULL, NULL, 0.0f, &trans);
	GLSpriteHandler->SetTransform(&mat);
	GLSpriteHandler->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK | D3DXSPRITE_ALPHABLEND);
#pragma endregion
	//------------------------------------------------------------------------
	
	//update time
	if(_timeForLevel > 0)
	{
		_timeForLevel -= time;
	}
	
	_Camera->Update(_aladdin);
	RECT r = GL_WndSize;
	r.top = GL_Height - _alpha * GL_Height;

	_BackgroundMng->UpdateRender(_Camera->GetCameraExpand(), time);
	
	//_aladdin->Update(time);

	_QuadTree->UpdateRender(_Camera->GetCameraExpand(), _aladdin, time);
	
	_aladdin->Render();
	
	//check fail game
	if(_aladdin->_life <= 0 && _aladdin->_State == DEAD && 
		!_isExitting)
	{
		//////////////////////////////////////////////////////////////////////////
		//fix lỗi camera còn di chuyển sau khi game over
		_aladdin->_vx = 0;
		_Camera->_vx = 0;
		//////////////////////////////////////////////////////////////////////////

		GL_CurForm = 0;
		GL_NextForm = 0;

		_isExitting = true;

		SoundManager::GetInst()->StopBgSound(SOUND_B_GAME1);

		LoseGameSence* screen = new LoseGameSence(_game, 1000, this);

		_game->AddSence(screen);
	}

	//------------------------------------------------------------------------
#pragma region End Render
	D3DXMATRIX matDefaut;
	D3DXMatrixTransformation2D(&matDefaut, NULL, 0.0f, NULL, NULL, 0.0f, NULL); 
	GLSpriteHandler->SetTransform(&matDefaut);
	
	//draw _life and gold  and info
	char text[100];

	//_life
	Sprite* sprLife = new Sprite(ResourceMng::GetInst()->GetTexture("image/life.png"), -1);
	sprLife->Render(40, 503);
	sprintf(text, "%d", _aladdin->_life);
	Writer::RenderFont2(text, 60, 520, 0.75f);

	//_apple
	Sprite* sprApple = new Sprite(ResourceMng::GetInst()->GetTexture("image/appleCount.png"), -1);
	sprApple->Render(700, 520);
	sprintf(text, "%d", _aladdin->_apple);
	Writer::RenderFont2(text, 715, 520, 0.75f);

	//_jewel
	if (_aladdin->_jewel > 0) {
		Sprite* sprJewel = new Sprite(ResourceMng::GetInst()->GetTexture("image/jewelCount.png"), -1);
		sprJewel->Render(630, 520);
		sprintf(text, "%d", _aladdin->_jewel);
		Writer::RenderFont2(text, 645, 520, 0.75f);
	}

	//_health meter
	Sprite* sprLamp = new Sprite(ResourceMng::GetInst()->GetTexture("image/lamp.png"), -1);
	sprLamp->Render(40, 50);
	sprSmoke->Render(136, 37);
	

	GLSpriteHandler->End();
#pragma endregion

	//mario complete map, go ahead
	if(_aladdin->_x >= GL_MapW - 10)
	{
		_aladdin->TurnRight();
		_aladdin->_vx = 0;
	}

	//check complete map pppppppppppppppppppppppppppppppppppppppppppppppppppppp
	if(_aladdin->GetRect().Right >= GL_MapW)
	{
		//sound win game
		//SoundManager::GetInst()->PlayEffSound(SOUND_E_WIN, false);

		//stop mario
		_aladdin->_vx = 0;

		//save game
		LoadNewMap();
	}


}

void PlaySence::LoadNewMap(void)
{
	//reset time
	_timeForLevel = TIME_FOR_LEVEL;

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

	//Load new game
	MapLoader::LoadMapFormFile(MapLoader::_mapNumber + 1, true, true, true, true);

	CRECT mapRECT = CRECT(0, 0, GL_MapW, GL_MapH);
	_QuadTree = new QuadTree(mapRECT);
	_BackgroundMng = new BackgroundManager();
	_Camera = new Camera(CRECT(GL_WndSize));

	MapLoader::TranslateMap(_QuadTree, _BackgroundMng, _aladdin, _timeForLevel);
	_BackgroundMng->Translate();
}

