#include "LBlock.h"
#include <QTime>

#define L_STATE 4

static int HILLS[L_STATE][L_SIZE][L_SIZE] =
{
	{
		{0,1,0},
		{0,1,0},
		{0,1,1},
	},
	{
		{0,0,0},
		{1,1,1},
		{1,0,0},
		},
		{
			{1,1,0},
			{0,1,0},
			{0,1,0},
		},
		{
			{0,0,1},
			{1,1,1},
			{0,0,0},
			},
};
LBlock::LBlock( IMap * pMap )
	:bFirstMove(false)
{
	m_pMap = pMap;
	iX = pMap->getWidth() / 2 - 1;
	iY = pMap->getHeight() - 1;

	qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
	iCurrentState = qrand() % L_STATE;

	for (int i = 0; i < L_SIZE; i++)
	{
		for (int j = 0; j < L_SIZE; j++)
		{
			blocks[i][j] = HILLS[iCurrentState][i][j];
		}
	}
}

bool LBlock::tryToRotateClockWise()
{
	int iNextIndex = (iCurrentState + 1) % L_STATE;
	int tempBlocks[L_SIZE][L_SIZE];
	for (int i = 0; i < L_SIZE; i++)
	{
		for (int j = 0; j < L_SIZE; j++)
		{
			tempBlocks[i][j] = HILLS[iNextIndex][i][j];
		}
	}

	for (int i = 0; i < L_SIZE; i++)
	{
		for (int j = 0; j < L_SIZE; j++)
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

	for (int i = 0; i < L_SIZE; i++)
	{
		for (int j = 0; j < L_SIZE; j++)
		{
			blocks[i][j] = tempBlocks[i][j];
		}
	}

	iCurrentState = iNextIndex;
	return true;
}

bool LBlock::tryToRotateAntiClockWise()
{
	int iPreIndex = (iCurrentState + L_STATE - 1) % L_STATE;
	int tempBlocks[L_SIZE][L_SIZE];
	for (int i = 0; i < L_SIZE; i++)
	{
		for (int j = 0; j < L_SIZE; j++)
		{
			tempBlocks[i][j] = HILLS[iPreIndex][i][j];
		}
	}

	for (int i = 0; i < L_SIZE; i++)
	{
		for (int j = 0; j < L_SIZE; j++)
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

	for (int i = 0; i < L_SIZE; i++)
	{
		for (int j = 0; j < L_SIZE; j++)
		{
			blocks[i][j] = tempBlocks[i][j];
		}
	}

	iCurrentState = iPreIndex;
	return true;
}

bool LBlock::tryToMoveLeft()
{
	int iLeftX = iX - 1;
	for (int i  = 0; i < L_SIZE; i++)
	{
		for (int j = 0; j < L_SIZE; j++)
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

bool LBlock::tryToMoveRight()
{
	int iRightX = iX + 1;
	for (int i  = 0; i < L_SIZE; i++)
	{
		for (int j = 0; j < L_SIZE; j++)
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

int LBlock::tryToMoveDown()
{
	int iDownY = iY - 1;
	for (int i  = 0; i < L_SIZE; i++)
	{
		for (int j = 0; j < L_SIZE; j++)
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

void LBlock::qryEffectiveBlocks( QList<PosStru> & poses ) const
{
	for (int i = 0; i < L_SIZE; i++)
	{
		for (int j = 0; j < L_SIZE; j++)
		{
			if (blocks[i][j] == 1)
			{
				poses << PosStru((iX + i) , (iY - j));
			}
		}
	}
}
