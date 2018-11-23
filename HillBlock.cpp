#include "HillBlock.h"

static int HILLS[STATE_SIZE][BASE_SIZE][BASE_SIZE] =
{
	{
		{0,1,0,0},
		{1,1,0,0},
		{0,1,0,0},
		{0,0,0,0},
	},
 	{
 		{0,1,0,0},
 		{1,1,1,0},
		{0,0,0,0},
		{0,0,0,0},
 	},
 	{
 		{0,1,0,0},
 		{0,1,1,0},
		{0,1,0,0},
		{0,0,0,0},
 	},
 	{
 		{0,0,0,0},
 		{1,1,1,0},
		{0,1,0,0},
		{0,0,0,0},
 	},
};
HillBlock::HillBlock( IMap * pMap )
	:BaseBlock(pMap)
{
	setStateBlocks(HILLS);
}
