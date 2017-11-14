#include "Rect.h"
#include <math.h>


CRECT::CRECT(void)
{
	_x	= 0;
	_w	= 0;
	_y	= 0;
	_h	= 0;
}

CRECT::CRECT(RECT r)
{
	_x	= r.left;
	_y	= r.top;
	_w	= r.right - r.left;
	_h	= r.bottom - r.top;
}

//LEFT - TOP- RIGHT - BOTTOM
CRECT::CRECT(float x, float y, float w, float h)
{
	_x	= x;
	_w	= y;
	_y	= w;
	_h	= h;
}

CRECT::~CRECT(void)
{
}

void CRECT::Move(float x, float y)
{
	_x	+= x;
	_w	+= x;
	_y	+= y;
	_h	+= y;
}
