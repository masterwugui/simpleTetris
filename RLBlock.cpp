#include "RLBlock.h"
#include <QTime>

#define RL_STATE 4

static int HILLS[RL_STATE][RL_SIZE][RL_SIZE] =
{
	{
		{0,1,0},
		{0,1,0},
		{1,1,0},
	},
	{
		{1,0,0},
		{1,1,1},
		{0,0,0},
		},
		{
			{0,1,1},
			{0,1,0},
			{0,1,0},
		},
		{
			{0,0,0},
			{1,1,1},
			{0,0,1},
			},
};
RLBlock::RLBlock( IMap * pMap )
	:bFirstMove(false)
{
	m_pMap = pMap;
	iX = pMap->getWidth() / 2 - 1;
	iY = pMap->getHeight() - 1;

	qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
	iCurrentState = qrand() % RL_STATE;

	for (int i = 0; i < RL_SIZE; i++)
	{
		for (int j = 0; j < RL_SIZE; j++)
		{
			blocks[i][j] = HILLS[iCurrentState][i][j];
		}
	}
}

bool RLBlock::tryToRotateClockWise()
{
	int iNextIndex = (iCurrentState + 1) % RL_STATE;
	int tempBlocks[RL_SIZE][RL_SIZE];
	for (int i = 0; i < RL_SIZE; i++)
	{
		for (int j = 0; j < RL_SIZE; j++)
		{
			tempBlocks[i][j] = HILLS[iNextIndex][i][j];
		}
	}

	for (int i = 0; i < RL_SIZE; i++)
	{
		for (int j = 0; j < RL_SIZE; j++)
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

	for (int i = 0; i < RL_SIZE; i++)
	{
		for (int j = 0; j < RL_SIZE; j++)
		{
			blocks[i][j] = tempBlocks[i][j];
		}
	}

	iCurrentState = iNextIndex;
	return true;
}

bool RLBlock::tryToRotateAntiClockWise()
{
	int iPreIndex = (iCurrentState + RL_STATE - 1) % RL_STATE;
	int tempBlocks[RL_SIZE][RL_SIZE];
	for (int i = 0; i < RL_SIZE; i++)
	{
		for (int j = 0; j < RL_SIZE; j++)
		{
			tempBlocks[i][j] = HILLS[iPreIndex][i][j];
		}
	}

	for (int i = 0; i < RL_SIZE; i++)
	{
		for (int j = 0; j < RL_SIZE; j++)
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

	for (int i = 0; i < RL_SIZE; i++)
	{
		for (int j = 0; j < RL_SIZE; j++)
		{
			blocks[i][j] = tempBlocks[i][j];
		}
	}

	iCurrentState = iPreIndex;
	return true;
}

bool RLBlock::tryToMoveLeft()
{
	int iLeftX = iX - 1;
	for (int i  = 0; i < RL_SIZE; i++)
	{
		for (int j = 0; j < RL_SIZE; j++)
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

bool RLBlock::tryToMoveRight()
{
	int iRightX = iX + 1;
	for (int i  = 0; i < RL_SIZE; i++)
	{
		for (int j = 0; j < RL_SIZE; j++)
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

int RLBlock::tryToMoveDown()
{
	int iDownY = iY - 1;
	for (int i  = 0; i < RL_SIZE; i++)
	{
		for (int j = 0; j < RL_SIZE; j++)
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

void RLBlock::qryEffectiveBlocks( QList<PosStru> & poses ) const
{
	for (int i = 0; i < RL_SIZE; i++)
	{
		for (int j = 0; j < RL_SIZE; j++)
		{
			if (blocks[i][j] == 1)
			{
				poses << PosStru((iX + i) , (iY - j));
			}
		}
	}
}
