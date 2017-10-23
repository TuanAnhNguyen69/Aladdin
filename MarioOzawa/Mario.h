#ifndef _MARIO_H_
#define _MARIO_H_


#include "Sprite.h"
#include "MyObject.h"

#include <vector>
#define ALADDIN_VX	0.5f	//velocity of mario
#define ALADDIN_VY	2
#define ALADDIN_MAX_JUMP 100
#define GRAVITY		0.01f	//gravity ratio
#define BOTTOM		600
#define DISTANCE_WITH_LAST_POSITION_X 400 //distance between the current position and last position to update last position
#define FALL_DEAD_HIGH 4	//the high mario fall out of game before reborn
#define DELTA_RECT_X 0 //delta to sub in x when call getRect
#define DELTA_RECT_Y 0 //delta to sub in y when call getRect

#define EXP_FOR_BRICK 5 //_point for exp
#define EXP_FOR_OBJECT 10
#define TIME_REBORN 1500 //thoi gian sau khi mario reborn hien thi o che do blur, truoc khi reborn hoan chinh

#define MARIO_VX_COMPLETE_MAP 0.50f
#define MARIO_DELTA_X_COMPLETE_MAP 400

#define MARIO_FIRE_TIME 250 //thoi gian giua 2 lan ban

using namespace std;

#pragma once

//Player ~ main character
class Aladdin : public MyObject
{
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
	void Move();
	void Reborn();
	void Climb();
	void Hang();
	void Bounce();



	//override
	virtual void CheckCollision(MyObject* obj);
	virtual void CheckTitleCollision(float &_vx,float &_vy,float &_nextX,float &_nextY,float _maxWidth,float _maxHeight,int _width,int _height);
	virtual void UpdateRealTimeCollision(int time,vector<MyObject*>*listcollision);
};

#endif
