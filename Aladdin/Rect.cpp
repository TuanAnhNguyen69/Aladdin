#include "Rect.h"
#include <math.h>


CRECT::CRECT(void)
{
	_x	= 0;
	Right	= 0;
	_y		= 0;
	Bottom	= 0;
}

CRECT::CRECT(RECT r)
{
	_x	= r.left;
	_y		= r.top;
	Right	= r.right;
	Bottom	= r.bottom;
}

//LEFT - TOP- RIGHT - BOTTOM
CRECT::CRECT(float left, float top, float right, float bottom)
{
	_x	= left;
	Right	= right;
	_y		= top;
	Bottom	= bottom;
}

CRECT::~CRECT(void)
{
}

RECT CRECT::ToRECT()
{
	RECT r = {_x, _y, Right, Bottom};
	return r;
}

//collision
bool CRECT::IsCollision(CRECT rect)
{
	bool c1 = (rect._x >= _x)
		&&(rect.Right <= Right)
		&&(rect._y >= _y)
		&&(rect.Bottom <= Bottom);

	float dh = (fabs(_y-rect.Bottom) > fabs((Bottom-rect._y))) ? fabs(_y-rect.Bottom) : fabs((Bottom-rect._y));
	float dw = (fabs(_x - rect.Right) > fabs(Right - rect._x)) ? fabs(_x-rect.Right) : fabs(Right - rect._x);

	return ((dw <= ((Right-_x)+(rect.Right-rect._x)))&&
		(dh <= ((Bottom-_y) + (rect.Bottom- rect._y))) || c1);
}

void CRECT::Move(float x, float y)
{
	_x	+= x;
	Right	+= x;
	_y		+= y;
	Bottom	+= y;
}

void CRECT::SetX(float x)
{
	float dx = x - _x;
	_x	+= dx;
	Right	+= dx;
}

void CRECT::SetY(float y)
{
	float dy = y - _y;
	_y		+= dy;
	Bottom	+= dy;
}
