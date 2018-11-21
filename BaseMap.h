#pragma once
#include <QVector>
#include "IMap.h"

class BaseMap : public IMap
{
public:
	BaseMap(const int iWidth, const int iHeight);
	virtual void merge(const IBlock &);
	virtual void start();
	virtual int getWidth();
	virtual int getHeight();
	virtual bool isBlock(const int iX, const int iY);
	virtual int calCount();
	virtual void qryEffectiveBlocks(QList<PosStru> &) const;

private:
	int m_iWidth;//
	int m_iHeight;
	int m_iPoint;//ตรทึ
	QVector<QVector<int>> m_map;

	inline void resetMap();
};