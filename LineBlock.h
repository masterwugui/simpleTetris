#pragma once
#include "IBlock.h"
#include "IMap.h"

#define LINE_SIZE 4
class LineBlock : public IBlock
{
public:
	LineBlock(IMap *);
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
	int blocks[LINE_SIZE][LINE_SIZE];

	bool bFirstMove;//�����һ���³�ʧ�� ��ʾ��Ϸ����
};