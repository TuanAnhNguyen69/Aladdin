//#ifndef _SWEPTAABB_H_
//#define _SWEPTAABB_H_
//
//#include <cmath>
//#include <algorithm>
//#include <limits>
//#include "MyObject.h"
//
//// describes an axis-aligned rectangle with a velocity
//// returns true if the boxes are colliding (velocities are not used)
//static bool AABBCheck(Box b1, Box b2)
//{
//	return !(b1._x + b1._w < b2._x || b1._x > b2._x + b2._w || b1._y < b2._y - b2._h || b1._y - b1._h > b2._y);
//}
//
//static bool AABBCheck1(Box b1, Box b2)
//{
//	return !(b1._x + b1._w <= b2._x || b1._x >= b2._x + b2._w || b1._y <= b2._y - b2._h || b1._y - b1._h >= b2._y);
//}
//
//// returns true if the boxes are colliding (velocities are not used)
//// moveX and moveY will return the movement the b1 must move to avoid the collision
//static bool AABB(Box b1, Box b2, float& moveX, float& moveY)
//{
//	moveX = moveY = 0.0f;
//
//	float l = b2._x - (b1._x + b1._w);
//	float r = (b2._x + b2._w) - b1._x;
//	float t = (b2._y - b2._h) - b1._y;
//	float b = b2._y - (b1._y - b1._h);
//
//	// check that there was a collision
//	if (l > 0 || r < 0 || t > 0 || b < 0)
//		return false;
//
//	// find the offset of both sides
//	moveX = abs(l) < r ? l : r;
//	moveY = abs(t) < b ? t : b;
//
//	// only use whichever offset is the smallest
//	if (abs(moveX) < abs(moveY))
//		moveY = 0.0f;
//	else
//		moveX = 0.0f;
//
//	return true;
//}
//
//// returns a box the spans both a current box and the destination box
//static Box GetSweptBroadphaseBox(Box b)
//{
//	Box broadphasebox(0.0f, 0.0f, 0.0f, 0.0f);
//
//	broadphasebox._x = b._vx > 0 ? b._x : b._x + b._vx;
//	broadphasebox._y = b._vy > 0 ? b._y + b._vy : b._y;
//	broadphasebox._w = b._vx > 0 ? b._vx + b._w : b._w - b._vx;
//	broadphasebox._h = b._vy > 0 ? b._vy + b._h : b._h - b._vy;
//
//	return broadphasebox;
//}
//
//// performs collision detection on moving box b1 and static box b2
//// returns the time that the collision occured (where 0 is the start of the movement and 1 is the destination)
//// getting the new position can be retrieved by box._x = box._x + box._vx * collisiontime
//// normalx and normaly return the normal of the collided surface (this can be used to do a response)
//static float SweptAABB(Box b1, Box b2, float& normalx, float& normaly)
//{
//	float xInvEntry, yInvEntry;
//	float xInvExit, yInvExit;
//
//	// find the distance between the objects on the near and far sides for both x and y
//	if (b1._vx > 0.0f)
//	{
//		xInvEntry = b2._x - (b1._x + b1._w);
//		xInvExit = (b2._x + b2._w) - b1._x;
//	}
//	else
//	{
//		xInvEntry = (b2._x + b2._w) - b1._x;
//		xInvExit = b2._x - (b1._x + b1._w);
//	}
//
//	if (b1._vy > 0.0f)
//	{
//		yInvEntry = (b2._y - b2._h) - b1._y;
//		yInvExit = b2._y - (b1._y - b1._h);
//	}
//	else
//	{
//		yInvEntry = b2._y - (b1._y - b1._h);
//		yInvExit = (b2._y - b2._h) - b1._y;
//	}
//
//	// find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
//	float xEntry, yEntry;
//	float xExit, yExit;
//
//	if (b1._vx == 0.0f)
//	{
//		xEntry = -std::numeric_limits<float>::infinity();
//		xExit = std::numeric_limits<float>::infinity();
//	}
//	else
//	{
//		xEntry = xInvEntry / b1._vx;
//		xExit = xInvExit / b1._vx;
//	}
//
//	if (b1._vy == 0.0f)
//	{
//		yEntry = -std::numeric_limits<float>::infinity();
//		yExit = std::numeric_limits<float>::infinity();
//	}
//	else
//	{
//		yEntry = yInvEntry / b1._vy;
//		yExit = yInvExit / b1._vy;
//	}
//
//	// find the earliest/latest times of collision
//	float entryTime = std::fmaxf(xEntry, yEntry);
//	float exitTime = std::fminf(xExit, yExit);
//
//	// if there was no collision
//	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
//	{
//		normalx = 0.0f;
//		normaly = 0.0f;
//		return 1.0f;
//	}
//	else // if there was a collision
//	{
//		// calculate normal of collided surface
//		if (xEntry > yEntry)
//		{
//			if (xInvEntry < 0.0f)
//			{
//				normalx = 1.0f;
//				normaly = 0.0f;
//			}
//			else
//			{
//				normalx = -1.0f;
//				normaly = 0.0f;
//			}
//		}
//		else
//		{
//			if (yInvEntry <= 0.0f)
//			{
//				normalx = 0.0f;
//				normaly = 1.0f;
//			}
//			else
//			{
//				normalx = 0.0f;
//				normaly = -1.0f;
//			}
//		}
//
//		// return the time of collision
//		return entryTime;
//	}
//}
//
//
//#endif