#pragma once
#include "MyObject.h"#include 
class NonPlayableCharacters :public MyObject
{
protected:
	CRECT activeRect;
public:
	NonPlayableCharacters();
	~NonPlayableCharacters();
};

