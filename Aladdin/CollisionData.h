#pragma once
//#include "MyObject.h"
enum EObject
{
	ALADDIN, // = 0
	APPLE,
	KNIFE,
	POT, // cái nồi úp xuống
	ROPE,
	BURNING_GROUND, // bãi than
	HANGER, // cây treo
	GROUND, // nền
	FALL_GROUND, // Mảnh nền rơi
	STAIR,
	BOUNCER, // Thanh nảy
	THROW_CIVILIAN, // thèn phóng dao
	SWORD_GUARD, // thèn cầm kiếm bình thường
	THIN_SWORD_GUARD, //thèn cầm kiếm gầy
	FAT_SWORD_GUARD, // thèn cầm kiếm mập
	BASKET_CIVILIAN, // cái gì giống cái hủ mà có cái ch ân đó, không biết đặt tên gì hết
	JAFAR, // con boss lúc còn hình người
	CAMEL, // lạc đà
	GENIE,// thèn đèn
	PEDDLER, //người bán rong
	BOTTLE,
	APPLE_ITEM,
	GENIE_HEAD,
	JEWEL,
	EXTRA_HEALTH,
	LIFE_UP
};
enum EDirect
{
	_x,
	_w,
	_y,
	_h,
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
	HANG_RELEASE,
	BOUNCE,
	FALL,
	LAND,
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

