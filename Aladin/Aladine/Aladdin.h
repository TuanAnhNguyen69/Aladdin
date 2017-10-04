#ifndef _MARIO_H_
#define _MARIO_H_


#include "Sprite.h"
#include "MyObject.h"

#include <vector>

using namespace std;

#pragma once

//Player ~ main character
class Aladdin : public MyObject
{
protected:
	int _startx; //the last position at that mario is (move or stand) and alive
	int _starty;

public:
	Sprite* _allSprite;
	Sprite* _curSprite;

	int jewel; // jewel to spend
	int life; // remain life
	int health; // remain health of current life
	int apple; // remain apple

	Aladdin(float x, float y);
	virtual ~Aladdin(void);

	virtual void Update(int time);
	virtual void Render();
	virtual CRECT GetRect();

	void Move();
	void Jump();
	void Stand();
	void Sit();
	void Fall();
	void ThrowApple();
	void Fight();
	void ClimbUp();
	void Hang();
	void Push();
	void Hit();
	void Dead();
	void Revive();

	//override
	virtual void CheckCollision(MyObject* obj);
	virtual void CheckTitleCollision(float &_vx,float &_vy,float &_nextX,float &_nextY,float _maxWidth,float _maxHeight,int _width,int _height);
	virtual void UpdateRealTimeCollision(int time,vector<MyObject*>*listcollision);
};

#endif
