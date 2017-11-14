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
	_alive = true;
	_turnRight = true;
}


MyObject::~MyObject(void)
{

}

CRECT MyObject::GetRect()
{
	return CRECT(_x, _y, _w, _h);
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

void MyObject::onCollision(MyObject * otherObject, int normalx, int normaly)
{
}
