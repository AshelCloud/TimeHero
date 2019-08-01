#pragma execution_character_set("utf-8")
#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class Help
{
	int Chaptor;
	int Stage;
	int select;
	
	std::string text[10];

public:
	Help();
	const char* Return();
};
