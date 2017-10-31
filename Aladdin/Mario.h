#ifndef _MARIO_H_
#define _MARIO_H_


#include "Sprite.h"
#include "MyObject.h"

using namespace std;

#pragma once

//Player ~ main character
class Aladdin : public MyObject
{
private:
	int currentY;
	int standingTime;
	int movedDistance;
	bool _isControlable;
	bool _isHanging;
	bool _isClimbing;
protected:
	
	int _startx; //the last position at that mario is (move or stand) and alive
	int _starty;
	int time;

public:
	CRECT currentRECT;
	Sprite* _curSprite;

	int _point;
	int _life; //số mạng sống còn lại của mario
	int _apple;
	int _health;
	int _jewel;

	Aladdin(float x, float y);
	virtual ~Aladdin(void);

	virtual void Update(int time);
	virtual void Render();
	virtual CRECT GetRect();
	void TurnLeft();
	void TurnRight();
	void Jump();
	void Stand();
	void Sit();
	void LookUp();
	void Throw();
	void Slash();
	void Move(int keyCode = 0);
	void Stop();
	void Reborn();
	void Dead();
	void Climb();
	void Hang();
	void Bounce();
	void Hit();

	void resetStandingTime();
	void setControlable(bool isControlable);
	bool getControlable();
	bool isHanging();
	bool isClimbing();


	//override
	virtual void CheckCollision(MyObject* obj);
	virtual void CheckTitleCollision(float &_vx,float &_vy,float &_nextX,float &_nextY,float _maxWidth,float _maxHeight,int _width,int _height);
	virtual void UpdateRealTimeCollision(int time,vector<MyObject*>*listcollision);
};

#endif
