#pragma once
#include "BaseBlock.h"

class SquareBlock : public BaseBlock
{
public:
	SquareBlock(IMap *);
	virtual ~SquareBlock(){};

	virtual bool tryToRotateClockWise();//������ת
	virtual bool tryToRotateAntiClockWise();//������ת
};