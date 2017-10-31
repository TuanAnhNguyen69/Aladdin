#include "ZoomSence.h"
#include "SoundManager.h"

#define MAX_ZOOM (1.681)

BlankSence::BlankSence(Game* game, int timeAni, ISence* lastSence, ISence* nextSence)
	:GameSence(game, timeAni)
{
	_lastSence = lastSence;
	_nextSence = nextSence;
}

BlankSence::~BlankSence(void){}

void BlankSence::_Load()
{
	_spriteBlank = new Sprite(ResourceMng::GetInst()->GetTexture("image/imgBlank.png"), 0);
}

// nhan 1 lan
void BlankSence::_OnKeyDown(int keyCode){}

void BlankSence::_OnKeyUp(int keyCode){}

// nhan va giu
void BlankSence::_ProcessInput(){}

void BlankSence::_UpdateRender(int t)
{

	//update
	if(_state == SenceState::On)
	{
		_state = SenceState::Off;
		if(_nextSence == NULL)
		{
			PostQuitMessage(0);
		}
		else
		{
			GameSence* gs = (GameSence*)_lastSence;
			gs->_state = SenceState::Off;
			//
			_game->AddSence(_nextSence);
		}
	}

	//render
	float newW = (1-_alpha)*MAX_ZOOM*GL_Width;
	float newH = (1-_alpha)*MAX_ZOOM*GL_Height;

	RECT r1 = {0, 0, GL_Width, (GL_Height - newH) / 2 + 2}; //top
	GLDevice->ColorFill(GLBackBuffer, &r1, D3DCOLOR_XRGB(0, 0, 0));
	
	RECT r2 = {0, 0, (GL_Width - newW)/2 + 4, GL_Height}; //left
	GLDevice->ColorFill(GLBackBuffer, &r2, D3DCOLOR_XRGB(0, 0, 0));

	RECT r3 = {0, GL_Height - (GL_Height - newH)/2, GL_Width, GL_Height}; //bottom
	GLDevice->ColorFill(GLBackBuffer, &r3, D3DCOLOR_XRGB(0, 0, 0));

	RECT r4 = {GL_Width - (GL_Width - newW)/2, 0, GL_Width, GL_Height}; //right
	GLDevice->ColorFill(GLBackBuffer, &r4, D3DCOLOR_XRGB(0, 0, 0));
	
	GLSpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	//
	_spriteBlank->RenderTransform(0, 0, D3DXVECTOR2((1-_alpha)*MAX_ZOOM, (1-_alpha)*MAX_ZOOM), 0, 0.5);
	//
	GLSpriteHandler->End();
}


