#pragma once
#include <QList>

enum MOVESTATE
{
	STATE_END,//结束
	STATE_FAIL,//失败
	STATE_SUCCESS,//成功
};

struct PosStru
{
	int iX;
	int iY;

	PosStru(int iX, int iY)
	{
		this->iX = iX;
		this->iY = iY;
	}

	PosStru()
	{
		iX = 0;
		iY = 0;
	}
};
//方块基类
class IBlock
{
public:
	virtual bool tryToRotateClockWise() = 0;//尝试左转
	virtual bool tryToRotateAntiClockWise() = 0;//尝试右转
	virtual bool tryToMoveLeft() = 0;//尝试左移
	virtual bool tryToMoveRight() = 0;//尝试右移
	virtual int	 tryToMoveDown() = 0;//尝试下移
	virtual void qryEffectiveBlocks(QList<PosStru> &) const = 0;//查询有效的方块点
};