#ifndef SIMPLETETRIS_H
#define SIMPLETETRIS_H

#include <QtGui/QMainWindow>
#include <QTimer>
#include "ui_simpletetris.h"
#include "TetrisWidget.h"
#include <QPushButton>
#include <QLabel>

class SimpleTetris : public QMainWindow
{
	Q_OBJECT

public:
	SimpleTetris(QWidget *parent = 0, Qt::WFlags flags = 0);
	~SimpleTetris();

	void keyPressEvent(QKeyEvent *);

private slots:
	void refreshScoreSlot(const int);
	void stopGameSlot();
	void startGameSlot();
private:
	Ui::SimpleTetrisClass ui;

	TetrisWidget *m_pTetrisWidget;

	QPushButton *m_pButton;//开始按钮
	QLabel *m_pScore;//得分
};

#endif // SIMPLETETRIS_H
