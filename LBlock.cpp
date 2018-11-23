#include "LBlock.h"
static int LS[STATE_SIZE][BASE_SIZE][BASE_SIZE] =
{
	{
		{0,1,0,0},
		{0,1,0,0},
		{0,1,1,0},
		{0,0,0,0},
	},
	{
		{0,0,0,0},
		{1,1,1,0},
		{1,0,0,0},
		{0,0,0,0},
	},
	{
		{1,1,0,0},
		{0,1,0,0},
		{0,1,0,0},
		{0,0,0,0},
	},
	{
		{0,0,1,0},
		{1,1,1,0},
		{0,0,0,0},
		{0,0,0,0},
	},
};
LBlock::LBlock( IMap * pMap )
	:BaseBlock(pMap)
{
	setStateBlocks(LS);
}

