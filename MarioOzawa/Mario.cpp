// tieu nun, fix all

#include "Mario.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "MapLoader.h"
#include "Writer.h"


Aladdin::Aladdin(float x, float y)	: MyObject(x, y)
{
	_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 0, 0, 100);
	_turnLeft = false;
	_State = STAND;
	_startx = _x = x;
	_starty = _y = y;
	_vx = 0;
	_vy = 0;
	_ID = EObject::ALADDIN;

	_life = 3;
	_apple = 10;
	_jewel = 1;
	_health = 8;
	_point = 0;

	this->currentRECT = CRECT(x, y, x + 30, y + 50);
}

Aladdin::~Aladdin(void)
{
	delete _curSprite;
	_curSprite = NULL;
}

void Aladdin::Update(int time)
{
	if ((this->_State == SIT || this->_State == LOOK_UP) && _curSprite->_index == _curSprite->_end)
		_curSprite->_start = _curSprite->_end;
	_curSprite->Update(time);


}

void Aladdin::Render()
{
	if(_turnLeft == false)
		_curSprite->RenderTransform((int)_x, (int)_y, D3DXVECTOR2(2.5f, 2.5f), 0); // for beautiful
	else 
		_curSprite->RenderTransform((int)_x - 60, (int)_y, D3DXVECTOR2(-2.5f, 2.5f), 0); // for beautiful
}

void Aladdin::TurnRight()
{
	this->_turnLeft = false;
}

void Aladdin::TurnLeft()
{
	this->_turnLeft = true;
}

void Aladdin::Jump()
{
	if (_y != 300) {
		if (_y < _y - ALADDIN_MAX_JUMP)
			_vy = -ALADDIN_VY;
		else
			_vy = ALADDIN_VY;
		_y += _vy;
	}
	if (this->_State == RUN)
		if (this->_State != JUMP_FORWARD) {
			_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 230, 236, 100);
			this->_State = JUMP_FORWARD;
			return;
		}
	if (this->_State != JUMP) {
		_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 253, 262, 100);
		this->_State = JUMP;
		return;
	}
}

void Aladdin::Stand()
{
	if (this->_State == STAND_THROWING || this->_State == STAND_SLASHING || this->_State == JUMP)
		if (_curSprite->_index != _curSprite->_end)
			return;
	if (this->_State != STAND)
		_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 1, 10, 100);
	this->_State = STAND;
}

//tan long
void Aladdin::Sit()
{
	if(this->_State != SIT)
		_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 161, 164, 100);
	this->_State = SIT;

}

void Aladdin::LookUp()
{
	if (this->_State != LOOK_UP)
		_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 138, 140, 100);
	this->_State = LOOK_UP;
}

void Aladdin::Throw()
{
	if (this->_State != STAND_THROWING)
		_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 69, 74, 100);
	this->_State = STAND_THROWING;
}

void Aladdin::Move()
{
	if (_turnLeft)
		this->_x -= 5;
	else
		this->_x += 5;
	if (this->_State == JUMP_FORWARD || this->_State == JUMP)
		if (_curSprite->_index != _curSprite->_end)
			return;
	if (this->_State != RUN)
		_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 368, 379, 40);
	this->_State = RUN;
}

void Aladdin::CheckCollision(MyObject* obj)
{
	
}

CRECT Aladdin::GetRect()
{
	return this->currentRECT;
}


void Aladdin::UpdateRealTimeCollision(int time, vector<MyObject*>* listcollision)
{

}

void Aladdin::CheckTitleCollision(float &_vx,float &_vy,float &_nextX,float &_nextY,float _maxWidth,float _maxHeight,int _width,int _height)
{

}