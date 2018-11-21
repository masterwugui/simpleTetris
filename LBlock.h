#pragma once
#include "IBlock.h"
#include "IMap.h"

#define L_SIZE 3
class LBlock : public IBlock
{
public:
	LBlock(IMap *);
	virtual ~LBlock(){};
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
	int blocks[L_SIZE][L_SIZE];

	bool bFirstMove;//�����һ���³�ʧ�� ��ʾ��Ϸ����
};
