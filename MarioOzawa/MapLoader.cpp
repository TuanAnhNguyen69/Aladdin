#pragma once

#include "MapLoader.h"
#include "Global.h"


//macro to get byte in color
//#define getA© ((©&0xff000000)>>24)
//#define getR© ((©&0x00ff0000)>>16)
//#define getG© ((©&0x0000ff00)>>8)
//#define getB© (©&0x000000ff)

int MapLoader::_mapW = 0;
int MapLoader::_mapH = 0;
 int MapLoader::_mapNumber = 0; //số thứ tự của map
 int MapLoader::_gold = -1;
 int MapLoader::_life = -1;
 int MapLoader::_exp = -1;
 int MapLoader::_curForm = -1;
 int MapLoader::_nextForm = -1;
 int MapLoader::_marioState = -1; //state of mario
 int MapLoader::_timeInGame = -1;

 int MapLoader::_mariox = 2; //vị trí của mario TILE
 int MapLoader::_marioy = 2;

 int** MapLoader::_board = NULL;
 int** MapLoader::_boardState = NULL;
 LPDIRECT3DTEXTURE9 MapLoader::_mapTexture = NULL;

MapLoader::MapLoader(void)
{
}

MapLoader::~MapLoader(void)
{
	delete _mapTexture;
	delete[] _board;
	delete[] _boardState;

	_mapTexture = NULL;
	_board = NULL;
	_boardState = NULL;
}

void MapLoader::LoadSavedGameFormFile(LPCTSTR _filesavegame)
{
		_mapNumber = 1;

		//load map from file map
		LoadMapFormFile(_mapNumber, true, true, true, true);

}

HRESULT MapLoader::LoadMapFormFile (int mapNumber, bool isLoadMario, bool isLoadBackground, bool isLoadObjects, bool isLoadTileMap)
{
	_mapNumber = mapNumber;

	HRESULT	hr;
	D3DXIMAGE_INFO imageInfo;
	char fileName[50];
	sprintf(fileName, "map/map%d.png", mapNumber);
	hr = D3DXGetImageInfoFromFile( fileName , &imageInfo);

	if(FAILED(hr))
	{
		GLMessage("No map to load!!!");
		return hr;
	}

	//Create a raw map as a texture file with a 32-bit format
	hr = D3DXCreateTextureFromFileEx( 
		GLDevice ,							// DirectX device
		fileName ,							// File Path
		imageInfo.Width ,					// width
		imageInfo.Height ,					// Height
		imageInfo.MipLevels ,				// MipLevels
		D3DUSAGE_DYNAMIC ,					// D3DUSAGE
		D3DFMT_A8R8G8B8 ,					// Format
		D3DPOOL_DEFAULT  ,					// Pool
		D3DX_DEFAULT ,						// Filter
		D3DX_DEFAULT ,						// Mip filter
		0 ,									// Color key
		&imageInfo ,						// Image Info
		NULL ,								// NULL
		&_mapTexture );						// Output texture

	//Store the raw map width and height
	_mapW	= imageInfo.Width;
	_mapH	= imageInfo.Height;

	GL_MapW = _mapW * TILE;
	GL_MapH = _mapH * TILE;

	GL_MapTileW = _mapW;
	GL_MapTileH = _mapH;

	if(FAILED(hr))
		return hr;
	
	//load pixel ID to board
	//
	D3DLOCKED_RECT		rect;
	D3DSURFACE_DESC		desc;
	DWORD				i,j;
	D3DCOLOR**			pColor;

	//First get the D3DSURFACE_DESC of this raw map
	hr = _mapTexture->GetLevelDesc( 0 , &desc );
	if(FAILED(hr))
		return hr;

	//We create a new D3DCOLOR 2D array has enough room to hold pixel color 
	pColor = new D3DCOLOR*[desc.Height];
	for ( i = 0 ; i < desc.Height ; ++i)
		pColor[i] = new D3DCOLOR[desc.Width];

	//Lock entire texture to read pixel
	hr = _mapTexture->LockRect( 0 , &rect , NULL , D3DLOCK_READONLY );
	if(FAILED(hr))
		return hr;

	BYTE* pBits = (BYTE*)rect.pBits;

	for (i = 0 ; i < desc.Height ; ++i)
	{
		for ( j = 0 ; j < desc.Width ; ++j)
		{
			DWORD index =( j*4 + ( i * (rect.Pitch) ));

			// Blue
			BYTE b = pBits[index];

			// Green
			BYTE g = pBits[index+1];

			// Red
			BYTE r = pBits[index+2];

			// Alpha
			BYTE a = pBits[index+3];
			D3DCOLOR color = D3DCOLOR_ARGB(a , r , g , b );
			pColor[i][j] = color;
		}
	}
	//Unlock texture
	_mapTexture->UnlockRect(0);

	//----------------------
	_board = new int*[_mapH];
	_boardState = new int*[_mapH];

	for(int i = 0; i < _mapH; i++)
	{
		_board[i] = new int[_mapW];
		_boardState[i] = new int[_mapW];
	}

	//gan gia tri ve 0
	for (int i = 0 ; i < _mapH; i++)	{
		for (int j = 0 ; j < _mapW; j++)	{			 
			_board[i][j] = 0;

			//default state for all object
			_boardState[i][j] = (int)AladdinState::ALIVE;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	for (i = 0 ; i < _mapH ; ++i)
	{
		for ( j = 0 ; j < _mapW ; ++j)
		{
			D3DCOLOR color = (pColor[i][j]);
			int blue = (color & 0x000000ff);
			
			if(blue == 0)
				continue;

			//MARIO
			if(blue == 1)
			{
				if(isLoadMario)
				{
					_mariox = 4;
					_marioy = 6;
				}
			}

			//BACKGROUND ID
			if((blue >= MIN_BG_ID && blue <= MAX_BG_ID) ||
				blue >= MIN_TILE_ID && blue <= MAX_TILE_ID)
			{
				if(isLoadBackground)
				{
					_board[i][j] = blue;
				}
			}

			//TILE MAP && BACKGROUND
			//BrickItem
			if(blue == 151 || blue == 153 || blue == 155 || blue == 156 || blue == 157)
			{
				if(isLoadTileMap)
				{
					_board[i][j] = blue;
				}
			}

			//TILE MAP ID / in Background
			if(blue >= MIN_TILE_ID && blue <= MAX_TILE_ID)
			{
				if(isLoadTileMap)
				{
					_board[i][j] = blue;
				}
			}
			
			//OBJECT ID
			if(blue >= MIN_OBJ_ID && blue <= MAX_OBJ_ID)
			{
				if(isLoadObjects)
				{
					_board[i][j] = blue;
				}
			}
		}
	}

	return S_OK;
}

void MapLoader::TranslateMap (QuadTree* quadtree, BackgroundManager* background, Aladdin* mario, int &timeInGame)
{
	//
	background->_mapW = _mapW;
	background->_mapH = _mapH;

	//
	TileMap::GetInst()->_mapW = _mapW;
	TileMap::GetInst()->_mapH = _mapH;

	//init array
	background->_board = new int*[_mapH];
	TileMap::GetInst()->_board = new int*[_mapH];

	for(int i = 0; i < _mapH; i++)
	{
		background->_board[i] = new int[_mapW];
		TileMap::GetInst()->_board[i] = new int[_mapW];
	}

	//gan gia tri ve 0
	for (int i = 0 ; i < _mapH; i++)	{
		for (int j = 0 ; j < _mapW; j++)	{
			background->_board[i][j] = 0;
			TileMap::GetInst()->_board[i][j] = 0;
		}
	}

	//time in game
	if(_timeInGame > -1)
		timeInGame = _timeInGame;

	//mario
	mario->_x = _mariox * TILE;
	mario->_y = _marioy * TILE;

	if(_curForm > -1 && _nextForm > -1 && _gold > -1 && _life > -1 && _exp > -1 && _marioState > -1)
	{
		GL_CurForm = _curForm;
		GL_NextForm = _nextForm;

		//mario->gold = _gold;
		mario->_life = _life;
		//mario->exp = _exp;
		mario->_State = (AladdinState)_marioState;
	}	

	//Insert Object
	int blue;
	for (int i = 0 ; i < _mapH ; ++i)
	{
		for (int j = 0 ; j < _mapW ; ++j)
		{
			blue = _board[i][j];

			if(blue == 0)
				continue;
			
			//BACKGROUND ID
			if((blue >= MIN_BG_ID && blue <= MAX_BG_ID) ||
				blue >= MIN_TILE_ID && blue <= MAX_TILE_ID)
			{
				background->_board[i][j] = blue;
			}
			
			//TILE MAP ID / in Background
			if(blue >= MIN_TILE_ID && blue <= MAX_TILE_ID)
			{
				TileMap::GetInst()->_board[i][j] = 1;

				if(blue == 103 || blue == 104 || blue == 105) //gound
				{
					if(i + 1 < _mapH)
						TileMap::GetInst()->_board[i + 1][j] = 1;
				}

				if(blue == 106) //pipe
				{
					if(i + 1 < _mapH && j + 1 < _mapW)
					{
						TileMap::GetInst()->_board[i + 1][j] = 1;
						TileMap::GetInst()->_board[i][j + 1] = 1;
						TileMap::GetInst()->_board[i + 1][j + 1] = 1;
					}

				}
			}
			
			
			//OBJECT ID
			if(blue >= MIN_OBJ_ID && blue <= MAX_OBJ_ID)
			{
				
				
			}
		}
	}
}

void MapLoader::SaveGameToFile(QuadTree* quadtree, Aladdin* mario, int timeInGame, LPCTSTR fileToSave)
{
	ofstream fout(fileToSave, ios_base::trunc);

	
}

void MapLoader::DeleteSavedGame(LPCTSTR fileSavedGame)
{
	
}
