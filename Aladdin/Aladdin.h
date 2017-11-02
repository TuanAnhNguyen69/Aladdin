#ifndef _MARIO_H_
#define _MARIO_H_


#include "MyObject.h"
#include "Camera.h"

using namespace std;

#pragma once

//Player ~ main character
class Aladdin : public MyObject
{
private:
	int currentSpriteIndex;
	int currentY;
	int standingTime;
	int movedDistance;
	bool _isControlable;
	bool _isHanging;
	bool _isClimbing;
	bool _isOnGround;
protected:
	
	int _startx; //the last position at that mario is (move or stand) and alive
	int _starty;
	int time;

public:
	AladdinState _State;
	CRECT currentRECT;
	Camera*		_camera;

	int _point;
	int _life; //số mạng sống còn lại của mario
	int _apple;
	int _health;
	int _jewel;

	Aladdin(float x, float y);
	~Aladdin(void);

	void Update(int time);
	void Render();
	CRECT GetRect();
	void Turn(int keyCode);
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
	void Land();
	void Bounce();
	void Hit();

	void resetStandingTime();
	void setControlable(bool isControlable);
	bool getControlable();
	bool isHanging();
	bool isClimbing();
	bool isOnGround();


	//override
	virtual void CheckCollision(MyObject* obj);
	virtual void CheckTitleCollision(float &_vx,float &_vy,float &_nextX,float &_nextY,float _maxWidth,float _maxHeight,int _width,int _height);
	virtual void UpdateRealTimeCollision(int time,vector<MyObject*>*listcollision);
};

#endif
