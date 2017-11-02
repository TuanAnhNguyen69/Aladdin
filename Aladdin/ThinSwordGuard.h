#pragma once
#include "Enemy.h"
class ThinSwordGuard :
	public Enemy
{
public:
	ThinSwordGuard();
	ThinSwordGuard(float x, float y);

	void Attack();
	//void Move();
	//void Active();
	//void AppleHit();
	~ThinSwordGuard();
};

