#include "MenuSence.h"
#include "PlaySence.h"
#include "OptionSence.h"
#include "SoundManager.h"
#include "ZoomSence.h"

int MenuSence::_curSelect = 0;

MenuSence::MenuSence(Game* game, int timeAni)
	:GameSence(game, timeAni)
{
	//_curSelect = 0;
}

MenuSence::~MenuSence(void)
{
}

void MenuSence::_Load()
{
	GLKeyBoard->Acquire();
	_sprSword = new Sprite(ResourceMng::GetInst()->GetTexture("image/imgMenuSword.png"), 100);
}

// nhan 1 lan
void MenuSence::_OnKeyDown(int keyCode){

	// control game //////////////////////////////////////////////////////////////////////////////////////////////////
	switch(keyCode){
		case DIK_RETURN:
			if (_curSelect == 0) { //play
				PlaySence* pl = new PlaySence(_game, 0);
				_game->AddSence(pl);
				this->_state = TransOff;
			} else { //option
				//goto option
				OptionSence* ot= new OptionSence(_game, 100);
				_game->AddSence(ot);
				_state = TransOff;
			}
			break;

		case DIK_UP:
			if(_curSelect > 0){
				_curSelect--;
			}
			break;

		case DIK_DOWN:
			if(_curSelect < MAX_MENU - 1){
				_curSelect++;
			}
			break;
	}
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
	//--------------------------------------------UPDATE------------------------------
	if(_sprSword->_index == 1 && _sprSword->_timeLocal >= _sprSword->_timeAni/7)
		_sprSword->SelectIndex(0);
	_sprSword->Update(t);


	//--------------------------------------------RENDER------------------------------
	RECT destRect = GL_WndSize;
	destRect.top = GL_Height - _alpha * GL_Height;
	
	ResourceMng::GetInst()->GetSurface("image/imgBgMenu.png")->Render(&destRect, &destRect);

	if(true){
		GLSpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		switch(_curSelect)
		{
			case 0:
				_sprSword->Render(205, 340);
				break;
				
			case 1:
				_sprSword->Render(205, 380);
				break;
		}

		GLSpriteHandler->End();
	}
}

