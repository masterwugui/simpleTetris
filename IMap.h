#pragma once
#include "IBlock.h"

//��ͼ�� 
class IMap
{
public:
	virtual void merge(const IBlock &) = 0;
	virtual void start() = 0;
	virtual int getWidth() = 0;
	virtual int getHeight() = 0;
	virtual bool isBlock(const int iX, const int iY) = 0;
	virtual int calCount() = 0;
	virtual void qryEffectiveBlocks(QList<PosStru> &) const = 0;//��ѯ��Ч�ķ����
};