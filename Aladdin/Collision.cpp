#include "Collision.h"


Collision::Collision()
{

}

MyObject* Collision::GetSweptBroadphaseBox(MyObject* B)
{
	return new MyObject(0,0);
}

float Collision::sweptAABB(MyObject * b1, MyObject * b2, int& normalx, int& normaly)
{	
	return 1;
}
void Collision::PreventMove(MyObject* b1, MyObject* b2, int nx, int ny)
{
}
bool Collision::AABBCheck(MyObject* b1, MyObject *b2)
{
	return true;
}

void Collision::CheckCollision(MyObject* b1, MyObject* b2)
{
}
void Collision::CollisionLine(MyObject* b1, MyObject* b2, int nx, int ny)
{
	
}
Collision::~Collision()
{
	
}
