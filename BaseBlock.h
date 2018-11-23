#pragma once
#include "IBlock.h"
#include "IMap.h"

#define BASE_SIZE 4
#define STATE_SIZE 4
class BaseBlock : public IBlock
{
public:
	BaseBlock(IMap *);
	virtual bool tryToRotateClockWise();//尝试左转
	virtual bool tryToRotateAntiClockWise();//尝试右转
	virtual bool tryToMoveLeft();//尝试左移
	virtual bool tryToMoveRight();//尝试右移
	virtual int tryToMoveDown();//尝试下移
	virtual void qryEffectiveBlocks(QList<PosStru> &) const;

	virtual void setStateBlocks(const int stateBlocks[STATE_SIZE][BASE_SIZE][BASE_SIZE]);
	/*inline void setState(const int iState){this->iCurrentState = iState;};
	inline int getState(){return this->iCurrentState;};*/
private:
	IMap *m_pMap;
	//当前偏移量 iX,iY统一为左上角点
	int iX;
	int iY;
	int iCurrentState;
	int BLOCKS[BASE_SIZE][BASE_SIZE];
	int STATE_BLOCKS[STATE_SIZE][BASE_SIZE][BASE_SIZE];

	bool bFirstMove;//如果第一次下沉失败 表示游戏结束
};