#pragma once

#include "gamesence.h"
#include "QuadTree.h"
#include "Camera.h"
#include "MapLoader.h"
#include "BackgroundManager.h"
#include "TileMap.h"

class MarioInPipeSence :
	public GameSence
{
public:
	QuadTree*	_QuadTree;
	Camera*		_Camera;
	MapLoader*	_MapLoader;
	BackgroundManager*	_BackgroundMng;

	Mario*	_aladdin;
	bool* IsVisiable;
	bool IsExitting;

	MarioInPipeSence(Game* game, bool* isVisible, int timeAni);
	~MarioInPipeSence(void);

	virtual void _UpdateRender(int t);
	virtual void _ProcessInput();
	virtual void _OnKeyDown(int keyCode);
	virtual void _OnKeyUp(int keyCode);
	virtual void _Load();
};

