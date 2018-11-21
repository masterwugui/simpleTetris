#include "RSBlock.h"
#include <QTime>

#define RS_STATE 4

static int RRSBlockS[RS_STATE][RS_SIZE][RS_SIZE] =
{
	{
		{0,0,1},
		{0,1,1},
		{0,1,0},
	},
	{
		{0,0,0},
		{1,1,0},
		{0,1,1},
		},
		{
			{0,1,0},
			{1,1,0},
			{1,0,0},
		},
		{
			{1,1,0},
			{0,1,1},
			{0,0,0},
			},
};
RSBlock::RSBlock( IMap * pMap )
	:bFirstMove(false)
{
	m_pMap = pMap;
	iX = pMap->getWidth() / 2 - 1;
	iY = pMap->getHeight() - 1;

	qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
	iCurrentState = qrand() % RS_STATE;

	for (int i = 0; i < RS_SIZE; i++)
	{
		for (int j = 0; j < RS_SIZE; j++)
		{
			blocks[i][j] = RRSBlockS[iCurrentState][i][j];
		}
	}
}

bool RSBlock::tryToRotateClockWise()
{
	int iNextIndex = (iCurrentState + 1) % RS_STATE;
	int tempBlocks[RS_SIZE][RS_SIZE];
	for (int i = 0; i < RS_SIZE; i++)
	{
		for (int j = 0; j < RS_SIZE; j++)
		{
			tempBlocks[i][j] = RRSBlockS[iNextIndex][i][j];
		}
	}

	for (int i = 0; i < RS_SIZE; i++)
	{
		for (int j = 0; j < RS_SIZE; j++)
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

	for (int i = 0; i < RS_SIZE; i++)
	{
		for (int j = 0; j < RS_SIZE; j++)
		{
			blocks[i][j] = tempBlocks[i][j];
		}
	}

	iCurrentState = iNextIndex;
	return true;
}

bool RSBlock::tryToRotateAntiClockWise()
{
	int iPreIndex = (iCurrentState + RS_STATE - 1) % RS_STATE;
	int tempBlocks[RS_SIZE][RS_SIZE];
	for (int i = 0; i < RS_SIZE; i++)
	{
		for (int j = 0; j < RS_SIZE; j++)
		{
			tempBlocks[i][j] = RRSBlockS[iPreIndex][i][j];
		}
	}

	for (int i = 0; i < RS_SIZE; i++)
	{
		for (int j = 0; j < RS_SIZE; j++)
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

	for (int i = 0; i < RS_SIZE; i++)
	{
		for (int j = 0; j < RS_SIZE; j++)
		{
			blocks[i][j] = tempBlocks[i][j];
		}
	}

	iCurrentState = iPreIndex;
	return true;
}

bool RSBlock::tryToMoveLeft()
{
	int iLeftX = iX - 1;
	for (int i  = 0; i < RS_SIZE; i++)
	{
		for (int j = 0; j < RS_SIZE; j++)
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

bool RSBlock::tryToMoveRight()
{
	int iRightX = iX + 1;
	for (int i  = 0; i < RS_SIZE; i++)
	{
		for (int j = 0; j < RS_SIZE; j++)
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

int RSBlock::tryToMoveDown()
{
	int iDownY = iY - 1;
	for (int i  = 0; i < RS_SIZE; i++)
	{
		for (int j = 0; j < RS_SIZE; j++)
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

void RSBlock::qryEffectiveBlocks( QList<PosStru> & poses ) const
{
	for (int i = 0; i < RS_SIZE; i++)
	{
		for (int j = 0; j < RS_SIZE; j++)
		{
			if (blocks[i][j] == 1)
			{
				poses << PosStru((iX + i) , (iY - j));
			}
		}
	}
}
