#include "SquareBlock.h"

static int SQUARES[STATE_SIZE][BASE_SIZE][BASE_SIZE] = 
{
	{
		{1,1,0,0},
		{1,1,0,0},
		{0,0,0,0},
		{0,0,0,0},
	},
	{
		{1,1,0,0},
		{1,1,0,0},
		{0,0,0,0},
		{0,0,0,0},
	},
	{
		{1,1,0,0},
		{1,1,0,0},
		{0,0,0,0},
		{0,0,0,0},
	},
	{
		{1,1,0,0},
		{1,1,0,0},
		{0,0,0,0},
		{0,0,0,0},
	},
};
SquareBlock::SquareBlock( IMap * pMap)
	:BaseBlock(pMap)
{
	setStateBlocks(SQUARES);
}

bool SquareBlock::tryToRotateClockWise()
{
	return true;
}

bool SquareBlock::tryToRotateAntiClockWise()
{
	return true;
}

