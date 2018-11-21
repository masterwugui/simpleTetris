#include "BaseMap.h"


BaseMap::BaseMap( const int iWidth, const int iHeight )
	:m_iPoint(0)
{
	this->m_iWidth = iWidth;
	this->m_iHeight = iHeight;
}

void BaseMap::merge( const IBlock & block)
{
	QList<PosStru> postions;
	block.qryEffectiveBlocks(postions);
	PosStru posStru;
	foreach(posStru, postions)
	{
		//m_map.at(posStru.iX).at(posStru.iY) = 1;
		m_map[posStru.iX][posStru.iY] = 1;
	}
}

void BaseMap::start()
{
	this->m_iPoint = 0;
	resetMap();
}

int BaseMap::getWidth()
{
	return this->m_iWidth;
}

int BaseMap::getHeight()
{
	return this->m_iHeight;
}

bool BaseMap::isBlock( const int iX, const int iY )
{
	if (iX < 0 ||
		iX >= m_map.size())
	{
		return true;
	}

	if (iY < 0 ||
		iY >= m_map.at(0).size())
	{
		return true;
	}

	return m_map.at(iX).at(iY) == 1;
}

int BaseMap::calCount()
{
	//查看是否有整行 可以消除
	QVector<int> deleteIndexs;
	for(int j = 0; j < m_iHeight; j++)
	{
		bool bLined = true;//是否连成一行
		for (int i = 0; i < m_iWidth; i++)
		{
			if (m_map[i][j] == 0)
			{
				//有一格为0即退出
				bLined = false;
				break;
			}
		}
		if (bLined)
		{
			deleteIndexs << j;
		}
	}

	if (deleteIndexs.isEmpty())
	{
		return m_iPoint;
	}

	QVector<QVector<int>> cpyMap = m_map;
	
	resetMap();
	
	int index = 0;
	for(int j = 0; j < m_iHeight; j++)
	{
		if (deleteIndexs.contains(j))
		{
			continue;
		}
		for (int i = 0; i < m_iWidth; i++)
		{
			m_map[i][index] = cpyMap[i][j];
		}
		index++;
	}

	m_iPoint += deleteIndexs.size();

	return m_iPoint;
}

void BaseMap::resetMap()
{
	m_map.clear();
	for (int i = 0; i < m_iWidth; i++)
	{
		QVector<int> tmpVector;
		for(int j = 0; j < m_iHeight; j++)
		{
			tmpVector.push_back(0);
		}
		m_map.push_back(tmpVector);
	}
}

void BaseMap::qryEffectiveBlocks( QList<PosStru> & poses) const
{
	for (int i = 0; i < m_map.size(); i++)
	{
		for (int j = 0; j < m_map.at(0).size(); j++)
		{
			if (m_map[i][j] == 1)
			{
				poses << PosStru(i, j);
			}
		}
	}
}
