#include "Enemy.h"


Enemy::Enemy()
{
	this->_health = 2;
}

Enemy::Enemy(float x, float y) : MyObject(x, y)
{
	this->_health = 2;
}

void Enemy::Move()
{
	_curSprite = this->_moveSprite;
}

void Enemy::Attack()
{
	_curSprite = this->_attackSprite;
}

void Enemy::Active()
{
	_curSprite = this->_activeSprite;
}

void Enemy::AppleHit()
{
	this->_health--;
	_curSprite = this->_hitSprite;
}

void Enemy::Dead()
{
	_curSprite = this->_deadSprite;
}

void Enemy::Update(int time)
{
	this->_curSprite->Update(time);
}


void Enemy::Render()
{
	if (_turnRight)
		_curSprite->RenderTransform((int)_x, (int)_y, D3DXVECTOR2(2.5f, 2.5f), 0); // for beautiful
	else
		_curSprite->RenderTransform((int)_x, (int)_y, D3DXVECTOR2(-2.5f, 2.5f), 0); // for beautiful
}

Enemy::~Enemy()
{
	
}
