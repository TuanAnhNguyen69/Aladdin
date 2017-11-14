#include "Collision.h"
#include <limits>
#include <iostream>
#include <algorithm>
Collision::Collision()
{

}

MyObject* Collision::GetSweptBroadphaseBox(MyObject* B)
{
	MyObject* broadphasebox;
	broadphasebox->_x = B->_vx > 0 ? B->_x : B->_x + B->_vx;
	broadphasebox->_y = B->_vy > 0 ? B->_y : B->_y + B->_vy;
	broadphasebox->_w = B->_vx > 0 ? B->_vx + B->_w : B->_w - B->_vx;
	broadphasebox->_h = B->_vy > 0 ? B->_vy + B->_h : B->_h - B->_vy;
	return broadphasebox;
}

float Collision::sweptAABB(MyObject * B1, MyObject * B2, int& normalx, int& normaly)
{	
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;
	// find the distance between the objects on the near and far sides for both x and y
	if (B1->_vx > 0.0f)
	{
		xInvEntry = B2->_x - (B1->_x + B1->_w);
		xInvExit = (B2->_x + B2->_w) - B1->_x;
	}
	else
	{
		xInvEntry = (B2->_x + B2->_w) - B1->_x;
		xInvExit = B2->_x - (B1->_x + B1->_w);
	}
	if (B1->_vy > 0.0f)
	{
		yInvEntry = B2->_y - (B1->_y + B1->_h);
		yInvExit = (B2->_y + B2->_h) - B1->_y;
	}
	else
	{
		yInvEntry = (B2->_y + B2->_h) - B1->_y;
		yInvExit = B2->_y - (B1->_y + B1->_h);
	}

	// find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
	float xEntry, yEntry;
	float xExit, yExit;
	if (B1->_vx == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / B1->_vx;
		xExit = xInvExit / B1->_vx;
	}
	if (B1->_vy == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / B1->_vy;
		yExit = yInvExit / B1->_vy;
	}

	// find the earliest/latest times of collision
	float entryTime = max(xEntry, yEntry);
	float exitTime = min(xExit, yExit);

	// if there was no collision
	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}

	else // if there was a collision
	{
		// calculate normal of collided surface
		if (xEntry > yEntry)
		{
			if (xInvEntry < 0.0f)
			{
				normalx = 1.0f;
				normaly = 0.0f;
			}
			else
			{
				normalx = -1.0f;
				normaly = 0.0f;
			}
		}
		else
		{
			if (yInvEntry < 0.0f)
			{
				normalx = 0.0f;
				normaly = 1.0f;
			}
			else
			{
				normalx = 0.0f;
				normaly = -1.0f;
			}
		}
		// return the time of collision
		return entryTime;
	}
}

bool Collision::AABBCheck(MyObject* B1, MyObject *B2)
{
	return !(B1->_x + B1->_w < B2->_x || B1->_x > B2->_x + B2->_w || B1->_y + B1->_h < B2->_y || B1->_y > B2->_y + B2->_h);
}

void Collision::CheckCollision(MyObject* b1, MyObject* b2)
{

	// box is the moving box
	// block is the static box
	MyObject* broadphasebox = GetSweptBroadphaseBox(b1);
	if (AABBCheck(broadphasebox, b2))
	{
		int normalx, normaly;
		float collisiontime = sweptAABB(b1, b2, normalx, normaly);
		b1->_x += b1->_vx* collisiontime;
		b1->_y += b1->_vy * collisiontime;
		if (collisiontime < 1.0f)
		{
			b1->onCollision(b2, normalx, normaly);
		}
	}
	delete broadphasebox;
}

Collision::~Collision()
{
	
}
