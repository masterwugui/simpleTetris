#include "SBlock.h"
#include <QTime>

#define S_STATE 4

static int SBLOCKS[S_STATE][S_SIZE][S_SIZE] =
{
	{
		{1,0,0},
		{1,1,0},
		{0,1,0},
	},
	{
		{0,1,1},
		{1,1,0},
		{0,0,0},
		},
		{
			{0,1,0},
			{0,1,1},
			{0,0,1},
		},
		{
			{0,0,0},
			{0,1,1},
			{1,1,0},
			},
};
SBlock::SBlock( IMap * pMap )
	:bFirstMove(false)
{
	m_pMap = pMap;
	iX = pMap->getWidth() / 2 - 1;
	iY = pMap->getHeight() - 1;

	qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
	iCurrentState = qrand() % S_STATE;

	for (int i = 0; i < S_SIZE; i++)
	{
		for (int j = 0; j < S_SIZE; j++)
		{
			blocks[i][j] = SBLOCKS[iCurrentState][i][j];
		}
	}
}

bool SBlock::tryToRotateClockWise()
{
	int iNextIndex = (iCurrentState + 1) % S_STATE;
	int tempBlocks[S_SIZE][S_SIZE];
	for (int i = 0; i < S_SIZE; i++)
	{
		for (int j = 0; j < S_SIZE; j++)
		{
			tempBlocks[i][j] = SBLOCKS[iNextIndex][i][j];
		}
	}

	for (int i = 0; i < S_SIZE; i++)
	{
		for (int j = 0; j < S_SIZE; j++)
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

	for (int i = 0; i < S_SIZE; i++)
	{
		for (int j = 0; j < S_SIZE; j++)
		{
			blocks[i][j] = tempBlocks[i][j];
		}
	}

	iCurrentState = iNextIndex;
	return true;
}

bool SBlock::tryToRotateAntiClockWise()
{
	int iPreIndex = (iCurrentState + S_STATE - 1) % S_STATE;
	int tempBlocks[S_SIZE][S_SIZE];
	for (int i = 0; i < S_SIZE; i++)
	{
		for (int j = 0; j < S_SIZE; j++)
		{
			tempBlocks[i][j] = SBLOCKS[iPreIndex][i][j];
		}
	}

	for (int i = 0; i < S_SIZE; i++)
	{
		for (int j = 0; j < S_SIZE; j++)
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

	for (int i = 0; i < S_SIZE; i++)
	{
		for (int j = 0; j < S_SIZE; j++)
		{
			blocks[i][j] = tempBlocks[i][j];
		}
	}

	iCurrentState = iPreIndex;
	return true;
}

bool SBlock::tryToMoveLeft()
{
	int iLeftX = iX - 1;
	for (int i  = 0; i < S_SIZE; i++)
	{
		for (int j = 0; j < S_SIZE; j++)
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

bool SBlock::tryToMoveRight()
{
	int iRightX = iX + 1;
	for (int i  = 0; i < S_SIZE; i++)
	{
		for (int j = 0; j < S_SIZE; j++)
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

int SBlock::tryToMoveDown()
{
	int iDownY = iY - 1;
	for (int i  = 0; i < S_SIZE; i++)
	{
		for (int j = 0; j < S_SIZE; j++)
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

void SBlock::qryEffectiveBlocks( QList<PosStru> & poses ) const
{
	for (int i = 0; i < S_SIZE; i++)
	{
		for (int j = 0; j < S_SIZE; j++)
		{
			if (blocks[i][j] == 1)
			{
				poses << PosStru((iX + i) , (iY - j));
			}
		}
	}
}
