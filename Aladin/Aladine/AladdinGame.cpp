#include <time.h>
#include <d3dx9.h>
#include "AladdinGame.h"
#include "Surface.h"
#include "ResourceManager.h"
#include "MenuSence.h"
#include "PlaySence.h"
#include "IntroSence.h"
#include "SoundManager.h"

AladdinGame::AladdinGame(HINSTANCE hInstance, char* Name, int Mode, int IsFullScreen, int FrameRate):
	Game(hInstance, Name, Mode, IsFullScreen, FrameRate)
{
	//TODO: Init game
}

AladdinGame::~AladdinGame()
{
	
}

void AladdinGame::LoadResources()
{
	SoundManager::GetInst();
}

//render before
void AladdinGame::RenderFrame(int t)
{
	//TODO: UPDATE-------------------------------------------------------
	//GameObject->Update(t);
}

void AladdinGame::ProcessInput(int t)
{
	//State
	//Nhan phim va giu
	
}

void AladdinGame::OnKeyDown(int keyCode)
{
	
}

void AladdinGame::OnKeyUp(int KeyCode)
{
	//Buffer
	//Nhấn 1 lần
}