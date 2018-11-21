#pragma once
#include "IBlock.h"
#include "IMap.h"

#define HILL_SIZE 3
class HillBlock : public IBlock
{
public:
	HillBlock(IMap *);
	virtual ~HillBlock(){};
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
	int blocks[HILL_SIZE][HILL_SIZE];

	bool bFirstMove;//�����һ���³�ʧ�� ��ʾ��Ϸ����
};
