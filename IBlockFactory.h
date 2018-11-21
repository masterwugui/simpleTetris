#pragma once
#include "IBlock.h"

enum BlockType
{
	TYPE_SQUARE,
	TYPE_LINE,
	TYPE_HILL,
	TYPE_L,
	TYPE_RL,
	TYPE_S,
	TYPE_RS,
};

class IBlockFactory
{
public:
	virtual IBlock * createNewBlock() = 0;
};