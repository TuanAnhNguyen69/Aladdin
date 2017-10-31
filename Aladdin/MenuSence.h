#pragma once
#include "gamesence.h"

#define MAX_MENU 2

class MenuSence : public GameSence
{
public:
	static int _curSelect;
	Sprite* _sprSword;

	MenuSence(Game* game, int timeAni);
	virtual ~MenuSence(void);
	
	virtual void _UpdateRender(int t);
	virtual void _ProcessInput();
	virtual void _OnKeyDown(int keyCode);
	virtual void _OnKeyUp(int keyCode);
	virtual void _Load();
};

