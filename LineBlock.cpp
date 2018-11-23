#include "LineBlock.h"
static int LINES[STATE_SIZE][BASE_SIZE][BASE_SIZE] =
{
	{
		{0,0,0,0},
		{0,0,0,0},
		{1,1,1,1},
		{0,0,0,0},
	},
	{
		{0,0,1,0},
		{0,0,1,0},
		{0,0,1,0},
		{0,0,1,0},
	},
	{
		{0,0,0,0},
		{0,0,0,0},
		{1,1,1,1},
		{0,0,0,0},
	},
		{
			{0,0,1,0},
			{0,0,1,0},
			{0,0,1,0},
			{0,0,1,0},
		},
};
LineBlock::LineBlock( IMap * pMap )
	:BaseBlock(pMap)
{
	setStateBlocks(LINES);
}
