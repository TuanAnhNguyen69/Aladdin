#include "ResourceManager.h"
#include <string.h>

ResourceMng* ResourceMng::_instance = NULL;

ResourceMng::ResourceMng()
{
	//background image
	for (int i = MIN_BG_ID; i <= MAX_BG_ID; ++i)
	{
		char* fileName;
		fileName = new char[50];
		sprintf(fileName, "tile/%d.png", i);
		//
		if(i == 15 || i == 18) //cloud, grass
		{
			_listTexture.push_back(new TEXTURE(fileName, 3, 1, 3));
		}
		else
		{
			_listTexture.push_back(new TEXTURE(fileName, 1, 1, 1));
		}
	}

	//ground image
	for (int i = MIN_GROUND_ID; i <= MAX_GROUND_ID; ++i)
	{
		char* fileName;
		fileName = new char[50];
		sprintf(fileName, "tile/%d.png", i);
		//
		_listTexture.push_back(new TEXTURE(fileName, 1, 1, 1));
	}
}

ResourceMng::~ResourceMng(void)
{
	if( ! _listTexture.empty()) _listTexture.clear();
	if( ! _listSurface.empty()) _listSurface.clear();
}

void ResourceMng::Release()
{
	if( ! _listTexture.empty()) _listTexture.clear();
	if( ! _listSurface.empty()) _listSurface.clear();
}

TEXTURE* ResourceMng::GetTexture(char*  fileName){
	int size = _listTexture.size();
	TEXTURE* tt;

	for(int i = 0 ; i < size; ++i){
		tt = _listTexture[i];

		if(strcmp(tt->FileName, fileName) == 0)
		{
			return tt;
		}
	}

	char t[100];
	sprintf(t, "[resourceMng.cpp] Can not get Texture[%s]", fileName);

	GLMessage(t);
	return NULL;
}

SURFACE* ResourceMng::GetSurface(char*  fileName){
	int size = _listSurface.size();
	SURFACE* sf;

	for(int i = 0 ; i < size; ++i){
		sf = _listSurface[i];
		if(strcmp(sf->FileName, fileName) == 0)
		{
			return sf;
		}
	}

	char t[100];
	sprintf(t, "[resourceMng.cpp] Can not get Surface:[%s]", fileName);
	GLMessage(t);

	return NULL;
}

ResourceMng* ResourceMng::GetInst(){
	if(_instance == NULL){
		_instance = new ResourceMng();
	}

	return _instance;
}

