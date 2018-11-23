#include "BaseBlock.h"
#include <QTime>

#define HILL_STATE 4
BaseBlock::BaseBlock( IMap * pMap )
	:bFirstMove(false)
{
	m_pMap = pMap;
	iX = pMap->getWidth() / 2 - 1;
	iY = pMap->getHeight() - 1;
}

bool BaseBlock::tryToRotateClockWise()
{
	int iNextIndex = (iCurrentState + 1) % HILL_STATE;
	int tempBlocks[BASE_SIZE][BASE_SIZE];
	for (int i = 0; i < BASE_SIZE; i++)
	{
		for (int j = 0; j < BASE_SIZE; j++)
		{
			tempBlocks[i][j] = STATE_BLOCKS[iNextIndex][i][j];
		}
	}

	for (int i = 0; i < BASE_SIZE; i++)
	{
		for (int j = 0; j < BASE_SIZE; j++)
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

	for (int i = 0; i < BASE_SIZE; i++)
	{
		for (int j = 0; j < BASE_SIZE; j++)
		{
			BLOCKS[i][j] = tempBlocks[i][j];
		}
	}

	iCurrentState = iNextIndex;
	return true;
}

bool BaseBlock::tryToRotateAntiClockWise()
{
	int iPreIndex = (iCurrentState + HILL_STATE - 1) % HILL_STATE;
	int tempBlocks[BASE_SIZE][BASE_SIZE];
	for (int i = 0; i < BASE_SIZE; i++)
	{
		for (int j = 0; j < BASE_SIZE; j++)
		{
			tempBlocks[i][j] = STATE_BLOCKS[iPreIndex][i][j];
		}
	}

	for (int i = 0; i < BASE_SIZE; i++)
	{
		for (int j = 0; j < BASE_SIZE; j++)
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

	for (int i = 0; i < BASE_SIZE; i++)
	{
		for (int j = 0; j < BASE_SIZE; j++)
		{
			BLOCKS[i][j] = tempBlocks[i][j];
		}
	}

	iCurrentState = iPreIndex;
	return true;
}

bool BaseBlock::tryToMoveLeft()
{
	int iLeftX = iX - 1;
	for (int i  = 0; i < BASE_SIZE; i++)
	{
		for (int j = 0; j < BASE_SIZE; j++)
		{
			if (BLOCKS[i][j] == 1 &&
				m_pMap->isBlock(iLeftX + i, iY - j))
			{
				return false;
			}
		}
	}
	iX = iLeftX;
	return true;
}

bool BaseBlock::tryToMoveRight()
{
	int iRightX = iX + 1;
	for (int i  = 0; i < BASE_SIZE; i++)
	{
		for (int j = 0; j < BASE_SIZE; j++)
		{
			if (BLOCKS[i][j] == 1 &&
				m_pMap->isBlock(iRightX + i, iY - j))
			{
				return false;
			}
		}
	}
	iX = iRightX;
	return true;
}

int BaseBlock::tryToMoveDown()
{
	int iDownY = iY - 1;
	for (int i  = 0; i < BASE_SIZE; i++)
	{
		for (int j = 0; j < BASE_SIZE; j++)
		{
			if (BLOCKS[i][j] == 1 &&
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

void BaseBlock::qryEffectiveBlocks( QList<PosStru> & poses ) const
{
	for (int i = 0; i < BASE_SIZE; i++)
	{
		for (int j = 0; j < BASE_SIZE; j++)
		{
			if (BLOCKS[i][j] == 1)
			{
				poses << PosStru((iX + i) , (iY - j));
			}
		}
	}
}

void BaseBlock::setStateBlocks( const int stateBlocks[STATE_SIZE][BASE_SIZE][BASE_SIZE] )
{
	for (int k = 0; k < STATE_SIZE; k++)
	{
		for (int i = 0; i < BASE_SIZE; i++)
		{
			for (int j = 0; j < BASE_SIZE; j++)
			{
				STATE_BLOCKS[k][i][j] = stateBlocks[k][i][j];
			}
		}
	}
	
	qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
	iCurrentState = qrand() % HILL_STATE;

	for (int i = 0; i < BASE_SIZE; i++)
	{
		for (int j = 0; j < BASE_SIZE; j++)
		{
			BLOCKS[i][j] = STATE_BLOCKS[iCurrentState][i][j];
		}
	}
}
