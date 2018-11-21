#pragma once
#include "IBlockFactory.h"
#include "IMap.h"

#define TYPE_SIZE 7
class BlockRandomFactory : public IBlockFactory
{
public:
	BlockRandomFactory(void);

	virtual IBlock * createNewBlock();

	void setMap(IMap *);
private:
	IMap * m_pMap;
};