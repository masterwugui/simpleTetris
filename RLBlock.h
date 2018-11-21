#pragma once
#include "IBlock.h"
#include "IMap.h"

#define RL_SIZE 3
class RLBlock : public IBlock
{
public:
	RLBlock(IMap *);
	virtual ~RLBlock(){};
	virtual bool tryToRotateClockWise();//������ת
	virtual bool tryToRotateAntiClockWise();//������ת
	virtual bool tryToMoveLeft();//��������
	virtual bool tryToMoveRight();//��������
	virtual int tryToMoveDown();//��������
	virtual void qryEffectiveBlocks(QList<PosStru> &) const;

private:
	IMap *m_pMap;
	//��ǰƫ���� iX,iYͳһΪ���Ͻǵ�
	int iX;
	int iY;
	int iCurrentState;
	int blocks[RL_SIZE][RL_SIZE];

	bool bFirstMove;//�����һ���³�ʧ�� ��ʾ��Ϸ����
};
