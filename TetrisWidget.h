#pragma once
#include <QWidget>
#include <QTimer>
#include "IMap.h"
#include "IBlock.h"
#include "IMapFactory.h"
#include "IBlockFactory.h"

class TetrisWidget : public QWidget
{
	Q_OBJECT
public:
	TetrisWidget(QWidget *parent);
	virtual ~TetrisWidget();

	void startGame();//开始游戏

	void keyPressEvent(QKeyEvent *);
signals:
	void refreshScoreSignal(const int);
	void stopGameSignal();

private slots:
	void refreshEnvSlot();

private:
	void paintEvent(QPaintEvent *);

	
	inline void stopGame();//结束游戏

	IMap *m_pMap;
	IBlock *m_pBlock;
	IMapFactory *m_pMapFactory;
	IBlockFactory *m_pBlockFactory;

	QTimer *m_pTimer;
};