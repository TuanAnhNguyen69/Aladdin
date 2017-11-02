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
	_curSprite = new Sprite(this->_moveSprite);
}

void Enemy::Attack()
{
	//_curSprite = this->_moveSprite;
}

void Enemy::Active()
{
}

void Enemy::AppleHit()
{
	this->_health--;
}

void Enemy::Dead()
{
}
//
//void Enemy::Update()
//{
//}
//
//
//void Enemy::Render()
//{
//}

Enemy::~Enemy()
{
}
