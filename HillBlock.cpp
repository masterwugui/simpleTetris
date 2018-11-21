#include "HillBlock.h"
#include <QTime>

#define HILL_STATE 4

static int HILLS[HILL_STATE][HILL_SIZE][HILL_SIZE] =
{
	{
		{0,1,0},
		{1,1,0},
		{0,1,0},
	},
 	{
 		{0,1,0},
 		{1,1,1},
 		{0,0,0},
 	},
 	{
 		{0,1,0},
 		{0,1,1},
 		{0,1,0},
 	},
 	{
 		{0,0,0},
 		{1,1,1},
 		{0,1,0},
 	},
};
HillBlock::HillBlock( IMap * pMap )
	:bFirstMove(false)
{
	m_pMap = pMap;
	iX = pMap->getWidth() / 2 - 1;
	iY = pMap->getHeight() - 1;

	qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
	iCurrentState = qrand() % HILL_STATE;

	for (int i = 0; i < HILL_SIZE; i++)
	{
		for (int j = 0; j < HILL_SIZE; j++)
		{
			blocks[i][j] = HILLS[iCurrentState][i][j];
		}
	}
}

bool HillBlock::tryToRotateClockWise()
{
	int iNextIndex = (iCurrentState + 1) % HILL_STATE;
	int tempBlocks[HILL_SIZE][HILL_SIZE];
	for (int i = 0; i < HILL_SIZE; i++)
	{
		for (int j = 0; j < HILL_SIZE; j++)
		{
			tempBlocks[i][j] = HILLS[iNextIndex][i][j];
		}
	}

	for (int i = 0; i < HILL_SIZE; i++)
	{
		for (int j = 0; j < HILL_SIZE; j++)
		{
			if (tempBlocks[i][j] == 1)
			{
				if (m_pMap->isBlock(iX + i, iY - j))
				{
					return false;
				}
			}
		}
	}

	for (int i = 0; i < HILL_SIZE; i++)
	{
		for (int j = 0; j < HILL_SIZE; j++)
		{
			blocks[i][j] = tempBlocks[i][j];
		}
	}

	iCurrentState = iNextIndex;
	return true;
}

bool HillBlock::tryToRotateAntiClockWise()
{
	int iPreIndex = (iCurrentState + HILL_STATE - 1) % HILL_STATE;
	int tempBlocks[HILL_SIZE][HILL_SIZE];
	for (int i = 0; i < HILL_SIZE; i++)
	{
		for (int j = 0; j < HILL_SIZE; j++)
		{
			tempBlocks[i][j] = HILLS[iPreIndex][i][j];
		}
	}

	for (int i = 0; i < HILL_SIZE; i++)
	{
		for (int j = 0; j < HILL_SIZE; j++)
		{
			if (tempBlocks[i][j] == 1)
			{
				if (m_pMap->isBlock(iX + i, iY - j))
				{
					return false;
				}
			}
		}
	}

	for (int i = 0; i < HILL_SIZE; i++)
	{
		for (int j = 0; j < HILL_SIZE; j++)
		{
			blocks[i][j] = tempBlocks[i][j];
		}
	}

	iCurrentState = iPreIndex;
	return true;
}

bool HillBlock::tryToMoveLeft()
{
	int iLeftX = iX - 1;
	for (int i  = 0; i < HILL_SIZE; i++)
	{
		for (int j = 0; j < HILL_SIZE; j++)
		{
			if (blocks[i][j] == 1 &&
				m_pMap->isBlock(iLeftX + i, iY - j))
			{
				return false;
			}
		}
	}
	iX = iLeftX;
	return true;
}

bool HillBlock::tryToMoveRight()
{
	int iRightX = iX + 1;
	for (int i  = 0; i < HILL_SIZE; i++)
	{
		for (int j = 0; j < HILL_SIZE; j++)
		{
			if (blocks[i][j] == 1 &&
				m_pMap->isBlock(iRightX + i, iY - j))
			{
				return false;
			}
		}
	}
	iX = iRightX;
	return true;
}

int HillBlock::tryToMoveDown()
{
	int iDownY = iY - 1;
	for (int i  = 0; i < HILL_SIZE; i++)
	{
		for (int j = 0; j < HILL_SIZE; j++)
		{
			if (blocks[i][j] == 1 &&
				m_pMap->isBlock(iX + i, iDownY - j))
			{
				if (!bFirstMove)
				{
					return STATE_END;
				}
				return STATE_FAIL;
			}
		}
	}
	iY = iDownY;
	bFirstMove = true;
	return STATE_SUCCESS;
}

void HillBlock::qryEffectiveBlocks( QList<PosStru> & poses ) const
{
	for (int i = 0; i < HILL_SIZE; i++)
	{
		for (int j = 0; j < HILL_SIZE; j++)
		{
			if (blocks[i][j] == 1)
			{
				poses << PosStru((iX + i) , (iY - j));
			}
		}
	}
}
