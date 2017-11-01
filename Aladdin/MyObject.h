#pragma once

#include "Rect.h"
#include "ListCollisionData.h"

using namespace std;

//super class for all object in game
struct Box
{
	Box() {}

	Box(float x, float y, float w, float h, float vx, float vy)
	{
		_x = x;
		_y = y;
		_w = w;
		_h = h;
		_vx = vx;
		_vy = vy;
	}

	Box(float x, float y, float w, float h)
	{
		_x = x;
		_y = y;
		_w = w;
		_h = h;
		_vx = 0;
		_vy = 0;
	}

	// position of top-left corner
	float _x, _y;

	// dimensions
	float _w, _h;

	// velocity
	float _vx, _vy;
};

class MyObject : public Box
{
public:
	AladdinState _State;
	bool _alive;
	//id to regonize what it is
	EObject _ID;

	//check if it is turn left or turn right
	//0: Left | 1: Right
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
};

