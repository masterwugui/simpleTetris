#pragma once
#include "IBlock.h"
#include "IMap.h"

#define SQUARE_SIZE 2
class SquareBlock : public IBlock
{
public:
	SquareBlock(IMap *);
	virtual bool tryToRotateClockWise();//尝试左转
	virtual bool tryToRotateAntiClockWise();//尝试右转
	virtual bool tryToMoveLeft();//尝试左移
	virtual bool tryToMoveRight();//尝试右移
	virtual int tryToMoveDown();//尝试下移
	virtual void qryEffectiveBlocks(QList<PosStru> &) const;

private:
	IMap *m_pMap;
	//当前偏移量 iX,iY统一为左上角点
	int iX;
	int iY;

	bool bFirstMove;//如果第一次下沉失败 表示游戏结束
};