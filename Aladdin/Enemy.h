#pragma once
#include "MyObject.h"
class Enemy :
	public MyObject
{
protected:
	int _health;
	bool _isActive;
	Sprite _moveSprite;
	Sprite _attackSprite;
	Sprite _activeSprite;
	Sprite _hitSprite;
	Sprite _deadSprite;
public:
	Enemy();
	Enemy(float x, float y);
	virtual void Move();
	virtual void Attack();
	virtual void Active();
	virtual void AppleHit();
	virtual void Dead();
	//void Update();
	//void Render();
	~Enemy();
};

