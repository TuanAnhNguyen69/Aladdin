#pragma once

#include "gamesence.h"

class BlankSence :
	public GameSence
{
public:
	ISence* _lastSence;
	ISence* _nextSence;
	DWORD _startTime;
	Sprite* _spriteBlank;

	BlankSence(Game* game, int timeAni, ISence* lastSence, ISence* nextSence);
	~BlankSence(void);

	virtual void _UpdateRender(int t);
	virtual void _ProcessInput();
	virtual void _OnKeyDown(int keyCode);
	virtual void _OnKeyUp(int keyCode);
	virtual void _Load();
};


