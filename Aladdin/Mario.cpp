﻿// tieu nun, fix all

#include <ctime>
#include <stdlib.h>

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
	currentY = _y + 150;
	standingTime = 500;
	movedDistance = 0;

	_isControlable = true;
	_isHanging = false;
	_isClimbing = false;

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
	_x += _vx;
	_y -= _vy;
	if (_y < currentY - 170)
		_vy = -_vy;
	else if (_y == currentY) {
		_vy = 0;
	}
	if ((this->_State == SIT || this->_State == LOOK_UP) && _curSprite->_index == _curSprite->_end)
		_curSprite->_start = _curSprite->_end;

	if (this->_State == DEAD) {
		if (_curSprite->_index == 631)
			_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 644, 658, 100);
		if (_curSprite->_index == 658)
			this->Reborn();
	}

	if ((this->_State == REBORN || this->_State == HIT) && _curSprite->_index == _curSprite->_end) {
		this->_isControlable = true;
		this->Stand();
	}

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
	if (this->_State == JUMP || this->_State == JUMP_SLASH || this->_State == JUMP_THROW || this->_State == JUMP_FORWARD)
		return;
	_vy = 10;
	if (this->_State == MOVE)
		if (this->_State != JUMP_FORWARD) {
			_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 230, 236, 80);
			this->_State = JUMP_FORWARD;
			return;
		}
	if (this->_State != JUMP) {
		_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 253, 264, 50);
		this->_State = JUMP;
		return;
	}
}

void Aladdin::Stand()
{
	standingTime--;
	if (standingTime < 0) {

		if (this->_State == CHANGE_FOOT && this->_curSprite->_index != this->_curSprite->_end)
			return;

		if (this->_State != PLAYING_APPLE && this->_State != CHANGE_FOOT) {
			_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 23, 26, 100);
			this->_State = CHANGE_FOOT;
			return;
		}

		if (this->_State == PLAYING_APPLE && this->_curSprite->_index != this->_curSprite->_end)
			return;

		int randomval = rand() % 10;

		if (randomval < 5) {
			_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 27, 37, 100);
		}
		else
		{
			_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 46, 62, 100);
		}
		this->_State = PLAYING_APPLE;
		return;
	}

	if (this->_State == STAND_THROW || this->_State == STAND_SLASH || this->_State == JUMP
		|| this->_State == LOOK_UP_SLASH || this->_State == JUMP_SLASH || this->_State == JUMP_THROW 
		|| this->_State == STOP || this->_State == RUN_SLASH || this->_State == RUN_THROW)
		if (_curSprite->_index != _curSprite->_end)
			return;

	if (this->_State != STAND)
		_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 1, 10, 100);
	this->_State = STAND;
	return;
}

void Aladdin::Sit()
{
	if (this->_State == JUMP)
		return;

	if (this->_State == SIT_SLASH || this->_State == SIT_THROW) {
		if (this->_curSprite->_index != this->_curSprite->_end)
			return;

		_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 164, 164, 100);
		this->_State = SIT;
	}

	if (this->_State != SIT)
		_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 161, 164, 100);
	this->_State = SIT;
}

void Aladdin::LookUp()
{
	if (this->_State == LOOK_UP_SLASH && this->_curSprite->_index != this->_curSprite->_end)
		return;
	if (this->_State != LOOK_UP)
		_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 138, 140, 100);
	this->_State = LOOK_UP;
}

void Aladdin::Throw()
{
	if (_isHanging || _isClimbing) {
		if (this->_State == HANG_MOVE || this->_State == CLIMB_MOVE)
			return;
		if (this->_State != HANG_THROW)
			_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 483, 487, 50);
		this->_State = HANG_THROW;
		return;
	}

	if (this->_State == MOVE) {
		if (this->_State != RUN_THROW)
			_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 736, 740, 40);
		this->_State = RUN_THROW;
		return;
	}

	if (this->_State == SIT) {
		if (this->_State != SIT_THROW)
			_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 184, 188, 50);
		this->_State = SIT_THROW;
		return;
	}

	if (this->_State == JUMP || this->_State == JUMP_FORWARD) {
		if (this->_State != JUMP_THROW)
			_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 299, 303, 50);
		this->_State = JUMP_THROW;
		return;
	}

	if (this->_State != STAND_THROW)
		_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 69, 74, 50);
	this->_State = STAND_THROW;
	return;
}

void Aladdin::Slash()
{
	if (_isHanging || _isClimbing) {
		if (this->_State == HANG_MOVE || this->_State == CLIMB_MOVE)
			return;
		if (this->_State != HANG_SLASH)
			_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 506, 512, 50);
		this->_State = HANG_SLASH;
		return;
	}

	if (this->_State == MOVE) {
		if (this->_State != RUN_SLASH)
			_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 713, 718, 30);
		this->_State = RUN_SLASH;
		return;
	}

	if (this->_State == JUMP || this->_State == JUMP_FORWARD) {
		if (this->_State != JUMP_SLASH)
			_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 322, 327, 50);
		this->_State = JUMP_SLASH;
		return;
	}

	if (this->_State == SIT) {
		if (this->_State != SIT_SLASH)
			_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 207, 213, 50);
		this->_State = SIT_SLASH;
		return;
	}

	if (this->_State == LOOK_UP) {
		if (this->_State != LOOK_UP_SLASH)
			_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 115, 137, 50);
		this->_State = LOOK_UP_SLASH;
		return;
	}

	if (this->_State != STAND_SLASH)
		_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 92, 96, 50);
	this->_State = STAND_SLASH;
	return;
}

void Aladdin::Move(int keyCode)
{
	if (keyCode == DIK_UP)
		return;

	movedDistance += 5;
	if (_turnLeft)
		this->_vx = 5;
	else
		this->_vx = 5;

	if (this->_State == JUMP_FORWARD || this->_State == JUMP   || this->_State == JUMP_SLASH 
		|| this->_State == JUMP_THROW || this->_State == RUN_SLASH || this->_State == RUN_THROW)
		if (_curSprite->_index != _curSprite->_end)
			return;

	if (_isHanging) {
		if (this->_State != HANG_MOVE)
			_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 437, 446, 40);
		this->_State = HANG_MOVE;
		return;
	}

	if (this->_State != MOVE)
		_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 368, 379, 40);
	this->_State = MOVE;
	return;
}

void Aladdin::Stop()
{
	this->_vx = 0;
	if (movedDistance < 300)
		return;
	if (_isHanging)
		return;
	/*if (_isClimbing)
		this->_curSprite = */
	if (this->_State == JUMP_FORWARD || this->_State == JUMP || this->_State == JUMP_SLASH || this->_State == JUMP_THROW)
		if (_curSprite->_index != _curSprite->_end)
			return;
	if (this->_State != STOP)
		_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 391, 399, 50);
	this->_State = STOP;
	movedDistance = 0;
	return;
}

void Aladdin::Reborn()
{
	if (this->_State != REBORN)
		_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 667, 680, 50);
	this->_State = REBORN;
	this->_isControlable = false;
	return;
}

void Aladdin::Dead()
{
	if (this->_State != DEAD)
		_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 621, 631, 100);
	this->_State = DEAD;
	this->_isControlable = false;
	return;
}

void Aladdin::Climb()
{
	if (this->_State == HANG_SLASH || this->_State == HANG_THROW)
		if (this->_curSprite->_index != this->_curSprite->_end)
			return;
	if (this->_State != CLIMB)
		_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 460, 471, 70);
	this->_State = CLIMB;
	this->_isClimbing = true;
	return;
}

void Aladdin::Hang()
{
	if (this->_State == HANG_SLASH || this->_State == HANG_THROW) 
		if (this->_curSprite->_index != this->_curSprite->_end)
			return;
	if (this->_State != HANG)
		_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 460, 471, 70);
	this->_State = HANG;
	this->_isHanging = true;
	return;
}

void Aladdin::Hit()
{
	if (this->_State != HIT)
		_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 598, 603, 50);
	this->_State = HIT;
	this->_isHanging = false;
	return;
}

void Aladdin::resetStandingTime()
{
	standingTime = 500;
}

void Aladdin::setControlable(bool isControlable)
{
	this->_isControlable = isControlable;
}

bool Aladdin::getControlable()
{
	return this-> _isControlable;
}

bool Aladdin::isHanging()
{
	return this->_isHanging;
}

bool Aladdin::isClimbing()
{
	return this->_isClimbing;
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