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
	_w = 0;
	_h = 0;
	_State = AladdinState::ALIVE;
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
	return (_State != DEAD);
}

void MyObject::Update(int time)
{
}

void MyObject::Render()
{

}