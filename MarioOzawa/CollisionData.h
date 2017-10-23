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
	PLAYING_APPLE,
	STAND_THROWING,
	STAND_SLASHING,
	LOOK_UP,
	LOOK_UP_SLASHING,
	SIT,
	SIT_THROWING,
	SIT_SLASHING,
	JUMP,
	JUMP_FORWARD,
	JUMP_THROWING,
	JUMP_SLASHING,
	RUN,
	RUN_THROWING,
	RUN_SLASHING,
	ROPE_CLIMBING,
	ROPE_CLIMBING_THROW,
	ROPE_CLIMBING_SLASH,
	HANGING,
	HANGING_THROW,
	HANGING_SLASH,
	BOUNCING,
	LANDING,
	BIG_LANDING,
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

