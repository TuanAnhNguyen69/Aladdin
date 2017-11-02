#include "MyObject.h"
#include "Global.h"
#include "ResourceManager.h"
#include <math.h>
#include "TileMap.h"
#include "Writer.h"
MyObject::MyObject(float x, float y)
{
	_x = x;
	_y = y;
	_vx = 0;
	_vy = 0;
	Right = 0;
	Bottom = 0;
	_alive = true;
	_turnRight = true;
}


MyObject::~MyObject(void)
{

}

CRECT MyObject::GetRect()
{
	return CRECT(_x, _y, _x + TILE, _y + TILE);
}

bool MyObject::IsAlive(){
	return false;
}

void MyObject::Update(int time)
{
}

void MyObject::Render()
{

}

void MyObject::onColision()
{
}
