
#ifndef _MARIO_GAME_H_
#define _MARIO_GAME_H_

#include <d3dx9.h>

#include "Global.h"
#include "Game.h"
#include "Sprite.h"
#include "Aladdin.h"

//Main Game, implement class "Game"
class AladdinGame: public Game
{
public:
	AladdinGame(HINSTANCE hInstance, char* Name, int Mode, int IsFullScreen, int FrameRate);
	~AladdinGame();
		
protected:

	virtual void RenderFrame(int Delta);
	virtual void LoadResources();

	//handle input
	virtual void ProcessInput(int Delta);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};


#endif