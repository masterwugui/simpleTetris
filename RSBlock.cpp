#include "RSBlock.h"

static int RRS[STATE_SIZE][BASE_SIZE][BASE_SIZE] =
{
	{
		{0,0,1,0},
		{0,1,1,0},
		{0,1,0,0},
		{0,0,0,0},
	},
	{
		{0,0,0,0},
		{1,1,0,0},
		{0,1,1,0},
		{0,0,0,0},
	},
		{
			{0,1,0,0},
			{1,1,0,0},
			{1,0,0,0},
			{0,0,0,0},
		},
	{
		{1,1,0,0},
		{0,1,1,0},
		{0,0,0,0},
		{0,0,0,0},
	},
};
RSBlock::RSBlock( IMap * pMap )
	:BaseBlock(pMap)
{
	setStateBlocks(RRS);
}
