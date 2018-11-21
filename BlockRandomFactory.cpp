#include "BlockRandomFactory.h"
#include <QtGlobal>
#include <QTime>
#include "SquareBlock.h"
#include "LineBlock.h"
#include "HillBlock.h"
#include "RLBlock.h"
#include "LBlock.h"
#include "Sblock.h"
#include "RSBlock.h"

IBlock * BlockRandomFactory::createNewBlock()
{
	if (NULL == m_pMap)
	{
		return NULL;
	}
	qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
	int iBlockType = qrand()% TYPE_SIZE;
	switch(iBlockType)
	{
	case TYPE_SQUARE:
		return new SquareBlock(m_pMap);
	case TYPE_LINE:
		return new LineBlock(m_pMap);
	case TYPE_HILL:
		return new HillBlock(m_pMap);
	case TYPE_S:
		return new SBlock(m_pMap);
	case TYPE_RS:
		return new RSBlock(m_pMap);
	case TYPE_L:
		return new LBlock(m_pMap);
	case TYPE_RL:
		return new RLBlock(m_pMap);
	default:
		return NULL;
	}
}

BlockRandomFactory::BlockRandomFactory( void )
	:m_pMap(NULL)
{

}

void BlockRandomFactory::setMap( IMap * pMap)
{
	m_pMap = pMap;
}
