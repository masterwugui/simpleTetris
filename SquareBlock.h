#pragma once
#include "IBlock.h"
#include "IMap.h"

#define SQUARE_SIZE 2
class SquareBlock : public IBlock
{
public:
	SquareBlock(IMap *);
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

	bool bFirstMove;//�����һ���³�ʧ�� ��ʾ��Ϸ����
};