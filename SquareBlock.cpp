#include "SquareBlock.h"

static int square[SQUARE_SIZE][SQUARE_SIZE] = 
{
	{1,1},
	{1,1}
};
SquareBlock::SquareBlock( IMap * pMap)
	:bFirstMove(false)
{
	m_pMap = pMap;
	iX = pMap->getWidth() / 2 - 1;
	iY = pMap->getHeight() - 1;
}

bool SquareBlock::tryToRotateClockWise()
{
	return true;
}

bool SquareBlock::tryToRotateAntiClockWise()
{
	return true;
}

bool SquareBlock::tryToMoveLeft()
{
	if (iX == 0)
	{
		return false;
	}

	for (int i = 0; i < SQUARE_SIZE; i++)
	{
		if (m_pMap->isBlock(iX - 1, iY - i))
		{
			return false;
		}
	}
	iX -= 1;
	return true;
}

bool SquareBlock::tryToMoveRight()
{
	if (iX == m_pMap->getWidth() - 2)
	{
		return false;
	}

	for (int i = 0; i < SQUARE_SIZE; i++)
	{
		if (m_pMap->isBlock(iX + SQUARE_SIZE, iY - i))
		{
			return false;
		}
	}

	iX += 1;
	return true;
}

int SquareBlock::tryToMoveDown()
{
	if (iY == 1)
	{
		if (!bFirstMove)
		{
			return STATE_END;
		}
		return STATE_FAIL;
	}

	int iBottom = iY - SQUARE_SIZE;
	for (int i = 0; i < SQUARE_SIZE; i++)
	{
		if (m_pMap->isBlock(iX + i, iBottom))
		{
			if (!bFirstMove)
			{
				return STATE_END;
			}
			return STATE_FAIL;
		}
	}

	for (int i = 0; i < SQUARE_SIZE; i++)
	{
		for (int j = 0; j < SQUARE_SIZE; j++)
		{
			if (m_pMap->isBlock(iX + i, iY - j))
			{
				if (!bFirstMove)
				{
					return STATE_END;
				}
				return STATE_FAIL;
			}
		}
	}

	iY -= 1;
	bFirstMove = true;
	return STATE_SUCCESS;
}

void SquareBlock::qryEffectiveBlocks( QList<PosStru> & poses) const
{
	for (int i = 0; i < SQUARE_SIZE; i++)
	{
		for (int j = 0; j < SQUARE_SIZE; j++)
		{
			if (square[i][j] == 1)
			{
				poses << PosStru((iX + i) , (iY - j));
			}
		}
	}
}
