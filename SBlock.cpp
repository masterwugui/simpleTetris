#include "SBlock.h"

static int SS[STATE_SIZE][BASE_SIZE][BASE_SIZE]=
{
	{
		{1,0,0,0},
		{1,1,0,0},
		{0,1,0,0},
		{0,0,0,0},
	},
	{
		{0,1,1,0},
		{1,1,0,0},
		{0,0,0,0},
		{0,0,0,0},
		},
		{
			{0,1,0,0},
			{0,1,1,0},
			{0,0,1,0},
			{0,0,0,0},
		},
		{
			{0,0,0,0},
			{0,1,1,0},
			{1,1,0,0},
			{0,0,0,0},
			},
};
SBlock::SBlock( IMap * pMap )
	:BaseBlock(pMap)
{
	setStateBlocks(SS);
}
