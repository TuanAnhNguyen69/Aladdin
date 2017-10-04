#pragma once
#include "MyObject.h"
class Enemy :
	public MyObject
{
protected:
	int _damage;
	int _health;
public:
	Enemy();
	~Enemy();
};

