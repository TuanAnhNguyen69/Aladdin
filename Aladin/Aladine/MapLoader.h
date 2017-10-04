#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <fstream>
#include "QuadTree.h"
#include "BackgroundManager.h"
#include "TileMap.h"
#include "Aladdin.h"

#ifndef TIME_FOR_LEVEL
	#define TIME_FOR_LEVEL 150000
#endif

//load map from a bitmap
//+ save it to an array
//+ translate it to obj (add to quadtree, backgroundManader), or tile map(to check collision)
class MapLoader
{
public:
	static LPDIRECT3DTEXTURE9 _mapTexture;
	static int _mapW;	//number tile in width
	static int _mapH;	//number tile in heigh

	static int _mapNumber; //số thứ tự của map
	static int _jewel; // jewel to spend
	static int _life; // remain life
	static int _health; // remain health of current life
	static int _apple; // remain apple
	static int _timeInGame;

	static int _aladdinX; //vị trí của aladdin
	static int _aladdinY;

	static int **_board ;	//2dimention array to saved id of object in map
	static int **_boardState; //2dimention array to state of object in map

	MapLoader(void);
	~MapLoader(void);

	//load save status, befrore call load file map
	//before call LoadMapFromFile
	static void LoadSavedGameFormFile(LPCTSTR filesavegame);

	//load map from an bitmap, save id(int) to array **_terrain
	//after call LoadSavedGameFromFile
	static HRESULT LoadMapFormFile (int mapNumber, bool isLoadMario, bool isLoadBackground, bool isLoadObjects, bool isLoadTileMap);

	//translate from _board to object, or save to BackgroundManager and TileMap
	static void TranslateMap (QuadTree* quadtree, BackgroundManager* background, Aladdin* aladdin, int &timeInGame);

	//save game to file
	static void SaveGameToFile(QuadTree* quadtree, Aladdin* mario, int timeInGame, LPCTSTR fileToSave);

	//delete all saved game file and reset static value in MapLoader
	static void DeleteSavedGame(LPCTSTR fileSavedGame);
};

