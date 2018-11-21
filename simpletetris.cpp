#include "simpletetris.h"

SimpleTetris::SimpleTetris(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags),
	m_pTetrisWidget(NULL)
{
	ui.setupUi(this);
	resize(200, 150);
	m_pTetrisWidget = new TetrisWidget(this);
	ui.mainLayout->addWidget(m_pTetrisWidget, 0, Qt::AlignLeft | Qt::AlignTop);

	m_pButton = new QPushButton;
	m_pButton->setText("start");
	
	m_pScore = new QLabel;
	m_pScore->setText("score: ");

	QLabel *pLabel2 = new QLabel;
	pLabel2->setText("-> or d: move right.");

	QLabel *pLabel3 = new QLabel;
	pLabel3->setText("<- or a: move left.");

	QLabel *pLabel4 = new QLabel;
	pLabel4->setText("|^ or w: rotate.");

	QLabel *pLabel5 = new QLabel;
	pLabel5->setText("| or s: rotate.");

	QVBoxLayout *pLayout = new QVBoxLayout;
	pLayout->addWidget(m_pButton);
	pLayout->addWidget(m_pScore);
	pLayout->addWidget(pLabel2);
	pLayout->addWidget(pLabel3);
	pLayout->addWidget(pLabel4);
	pLayout->addWidget(pLabel5);

	ui.mainLayout->addLayout(pLayout);

	connect(m_pTetrisWidget, SIGNAL(refreshScoreSignal(const int)), this, SLOT(refreshScoreSlot(const int)));
	connect(m_pTetrisWidget, SIGNAL(stopGameSignal()), this, SLOT(stopGameSlot()));
	connect(m_pButton, SIGNAL(clicked()), this, SLOT(startGameSlot()));
}

SimpleTetris::~SimpleTetris()
{
}

void SimpleTetris::keyPressEvent( QKeyEvent * event)
{
	m_pTetrisWidget->keyPressEvent(event);
}

void SimpleTetris::startGameSlot()
{
	m_pButton->setEnabled(false);
	m_pScore->setText("score:");
	m_pTetrisWidget->startGame();
}

void SimpleTetris::stopGameSlot()
{
	m_pButton->setEnabled(true);
}

void SimpleTetris::refreshScoreSlot( const int iScore)
{
	m_pScore->setText(QString("score:%1 ").arg(iScore));
}
