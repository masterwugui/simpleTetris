#pragma once
#include "BaseBlock.h"

class SquareBlock : public BaseBlock
{
public:
	SquareBlock(IMap *);
	virtual ~SquareBlock(){};

	virtual bool tryToRotateClockWise();//Ё╒йтвСв╙
	virtual bool tryToRotateAntiClockWise();//Ё╒йтсрв╙
};