#include "RLBlock.h"
#include <QTime>

#define RL_STATE 4

static int RLS[STATE_SIZE][BASE_SIZE][BASE_SIZE] =
{
	{
		{0,1,0,0},
		{0,1,0,0},
		{1,1,0,0},
		{0,0,0,0},
	},
	{
		{1,0,0,0},
		{1,1,1,0},
		{0,0,0,0},
		{0,0,0,0},
	},
	{
		{0,1,1,0},
		{0,1,0,0},
		{0,1,0,0},
		{0,0,0,0},
	},
	{
		{0,0,0,0},
		{1,1,1,0},
		{0,0,1,0},
		{0,0,0,0},
	},
};
RLBlock::RLBlock( IMap * pMap )
	:BaseBlock(pMap)
{
	setStateBlocks(RLS);
}
