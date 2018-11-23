#pragma once
#include "IBlock.h"
#include "IMap.h"

#define BASE_SIZE 4
#define STATE_SIZE 4
class BaseBlock : public IBlock
{
public:
	BaseBlock(IMap *);
	virtual bool tryToRotateClockWise();//������ת
	virtual bool tryToRotateAntiClockWise();//������ת
	virtual bool tryToMoveLeft();//��������
	virtual bool tryToMoveRight();//��������
	virtual int tryToMoveDown();//��������
	virtual void qryEffectiveBlocks(QList<PosStru> &) const;

	virtual void setStateBlocks(const int stateBlocks[STATE_SIZE][BASE_SIZE][BASE_SIZE]);
	/*inline void setState(const int iState){this->iCurrentState = iState;};
	inline int getState(){return this->iCurrentState;};*/
private:
	IMap *m_pMap;
	//��ǰƫ���� iX,iYͳһΪ���Ͻǵ�
	int iX;
	int iY;
	int iCurrentState;
	int BLOCKS[BASE_SIZE][BASE_SIZE];
	int STATE_BLOCKS[STATE_SIZE][BASE_SIZE][BASE_SIZE];

	bool bFirstMove;//�����һ���³�ʧ�� ��ʾ��Ϸ����
};