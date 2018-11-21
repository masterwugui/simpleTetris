#pragma once
#include <QList>

enum MOVESTATE
{
	STATE_END,//����
	STATE_FAIL,//ʧ��
	STATE_SUCCESS,//�ɹ�
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
//�������
class IBlock
{
public:
	virtual bool tryToRotateClockWise() = 0;//������ת
	virtual bool tryToRotateAntiClockWise() = 0;//������ת
	virtual bool tryToMoveLeft() = 0;//��������
	virtual bool tryToMoveRight() = 0;//��������
	virtual int	 tryToMoveDown() = 0;//��������
	virtual void qryEffectiveBlocks(QList<PosStru> &) const = 0;//��ѯ��Ч�ķ����
};