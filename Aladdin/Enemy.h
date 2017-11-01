#pragma once
#include "MyObject.h"
class Enemy :
	public MyObject
{
protected:
	CRECT activeRect;
public:
	Enemy();
	~Enemy();
};

