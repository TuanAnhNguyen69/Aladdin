#pragma once

#include "Rect.h"
#include "ListCollisionData.h"
#include "Sprite.h"


using namespace std;

//super class for all object in game
class MyObject : public CRECT
{
public:
	int normalx, normaly;
	float _vx, _vy;
	Sprite* _curSprite;
	bool _alive;
	//id to regonize what it is
	EObject _ID;

	//check if it is turn left or turn right
	//0: _x | 1: _w
	bool _turnRight;
	//end tieu nun

	ListCollisionData _listCollisionData;

	MyObject() {}
	MyObject(float x, float y);
	//MyObject(const MyObject* obj);
	virtual ~MyObject(void);
	virtual CRECT GetRect();
	//obj is alive, can update and render
	virtual bool IsAlive();

	virtual void Update(int time);

	virtual void Render();

	virtual void onCollision(MyObject* otherObject, int normalx, int normaly);
};

