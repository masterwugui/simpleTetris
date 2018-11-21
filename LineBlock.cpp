#include "LineBlock.h"
#include <QTime>

#define LINE_STATE 2

static int HILLS[LINE_STATE][LINE_SIZE][LINE_SIZE] =
{
	{
		{1,1,1,1},
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0},
	},
	{
		{1,0,0,0},
		{1,0,0,0},
		{1,0,0,0},
		{1,0,0,0},
	},
};
LineBlock::LineBlock( IMap * pMap )
	:bFirstMove(false)
{
	m_pMap = pMap;
	iX = pMap->getWidth() / 2 - 1;
	iY = pMap->getHeight() - 1;

	qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
	iCurrentState = qrand() % LINE_STATE;

	for (int i = 0; i < LINE_SIZE; i++)
	{
		for (int j = 0; j < LINE_SIZE; j++)
		{
			blocks[i][j] = HILLS[iCurrentState][i][j];
		}
	}
}

bool LineBlock::tryToRotateClockWise()
{
	int iNextIndex = (iCurrentState + 1) % LINE_STATE;
	int tempBlocks[LINE_SIZE][LINE_SIZE];
	for (int i = 0; i < LINE_SIZE; i++)
	{
		for (int j = 0; j < LINE_SIZE; j++)
		{
			tempBlocks[i][j] = HILLS[iNextIndex][i][j];
		}
	}

	for (int i = 0; i < LINE_SIZE; i++)
	{
		for (int j = 0; j < LINE_SIZE; j++)
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

	for (int i = 0; i < LINE_SIZE; i++)
	{
		for (int j = 0; j < LINE_SIZE; j++)
		{
			blocks[i][j] = tempBlocks[i][j];
		}
	}

	iCurrentState = iNextIndex;
	return true;
}

bool LineBlock::tryToRotateAntiClockWise()
{
	int iPreIndex = (iCurrentState + LINE_STATE - 1) % LINE_STATE;
	int tempBlocks[LINE_SIZE][LINE_SIZE];
	for (int i = 0; i < LINE_SIZE; i++)
	{
		for (int j = 0; j < LINE_SIZE; j++)
		{
			tempBlocks[i][j] = HILLS[iPreIndex][i][j];
		}
	}

	for (int i = 0; i < LINE_SIZE; i++)
	{
		for (int j = 0; j < LINE_SIZE; j++)
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

	for (int i = 0; i < LINE_SIZE; i++)
	{
		for (int j = 0; j < LINE_SIZE; j++)
		{
			blocks[i][j] = tempBlocks[i][j];
		}
	}

	iCurrentState = iPreIndex;
	return true;
}

bool LineBlock::tryToMoveLeft()
{
	int iLeftX = iX - 1;
	for (int i  = 0; i < LINE_SIZE; i++)
	{
		for (int j = 0; j < LINE_SIZE; j++)
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

bool LineBlock::tryToMoveRight()
{
	int iRightX = iX + 1;
	for (int i  = 0; i < LINE_SIZE; i++)
	{
		for (int j = 0; j < LINE_SIZE; j++)
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

int LineBlock::tryToMoveDown()
{
	int iDownY = iY - 1;
	for (int i  = 0; i < LINE_SIZE; i++)
	{
		for (int j = 0; j < LINE_SIZE; j++)
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

void LineBlock::qryEffectiveBlocks( QList<PosStru> & poses ) const
{
	for (int i = 0; i < LINE_SIZE; i++)
	{
		for (int j = 0; j < LINE_SIZE; j++)
		{
			if (blocks[i][j] == 1)
			{
				poses << PosStru((iX + i) , (iY - j));
			}
		}
	}
}
