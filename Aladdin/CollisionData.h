#pragma once
//#include "MyObject.h"
enum EObject
{
	ALADDIN, // = 0
	APPLE,
	SWORD,
	KNIFE,
	ROPE,
	BURNING_LAND,
	HANGER,
	GROUND,
	FALL_GROUND,
	STAIR,
	BOUNCER
};
enum EDirect
{
	Left,
	Right,
	Top,
	Bottom,
	None
};
enum AladdinState{
	ALIVE,
	STAND,
	LOOK_TWO_SIDE,
	CHANGE_FOOT,
	PLAYING_APPLE,
	STAND_THROW,
	STAND_SLASH,
	LOOK_UP,
	LOOK_UP_SLASH,
	STOP,
	SIT,
	SIT_THROW,
	SIT_SLASH,
	JUMP,
	JUMP_FORWARD,
	JUMP_THROW,
	JUMP_SLASH,
	MOVE,
	RUN_THROW,
	RUN_SLASH,
	CLIMB,
	CLIMB_JUMP,
	CLIMB_MOVE,
	HANG,
	HANG_JUMP,
	HANG_MOVE,
	HANG_THROW,
	HANG_SLASH,
	BOUNCE,
	LANDING,
	BRAKE,
	HIT,
	DEAD,
	REBORN,
};
class CollisionData
{
public:
	EObject _ID;
	float _deltaX,_deltaY;
	EDirect _dirCollision;
	float _delta;
	int _indexObject;

	CollisionData(EObject ID,EDirect dirCollision,float deltaX,float deltaY,float delta,int indexObject);
	~CollisionData(void);
};

