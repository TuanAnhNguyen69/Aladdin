#pragma once

#include "Gamesence.h"
#include "Aladdin.h"
#include "QuadTree.h"
#include "Camera.h"
#include "MapLoader.h"
#include "BackgroundManager.h"
#include "TileMap.h"
#include "ChangeMapSence.h"

//sence of the battle and blood
class PlaySence :
	public GameSence
{
public:
	QuadTree*	_QuadTree;
	Camera*		_Camera;
	BackgroundManager*	_BackgroundMng;

	// tieu nun
	Aladdin*	_aladdin;

	//check if this sence is visiable
	bool IsVisiable;

	//check if is extiing
	bool _isExitting;
	
	PlaySence(Game* game, int timeAni);
	~PlaySence(void);

	virtual void _UpdateRender(int t);
	virtual void _ProcessInput();
	virtual void _OnKeyDown(int keyCode);
	virtual void _OnKeyUp(int keyCode);
	virtual void _Load();

	void LoadNewMap(void);
};

