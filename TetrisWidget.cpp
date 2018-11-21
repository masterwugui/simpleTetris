#include "TetrisWidget.h"
#include <QKeyEvent>
#include <QPainter>
#include "MapSimpleFactory.h"
#include "BlockRandomFactory.h"

#define BLOCK_SIZE 10
TetrisWidget::TetrisWidget(QWidget *parent)
	:m_pBlock(NULL),
	m_pMap(NULL),
	m_pMapFactory(NULL),
	m_pBlockFactory(NULL),
	m_pTimer(NULL)
{
	setFixedSize(100, 150);
	parent->installEventFilter(this);

	m_pMapFactory = new MapSimpleFactory;
	m_pMap = m_pMapFactory->createMap();

	m_pBlockFactory = new BlockRandomFactory;
	BlockRandomFactory * pBlockRandomFactory = dynamic_cast<BlockRandomFactory *>(m_pBlockFactory);
	if (NULL != pBlockRandomFactory)
	{
		pBlockRandomFactory->setMap(m_pMap);
	}

	m_pTimer = new QTimer(this);
	connect(m_pTimer, SIGNAL(timeout()), this, SLOT(refreshEnvSlot()));

	//startGame();//to delete
}

TetrisWidget::~TetrisWidget()
{
	if (NULL != m_pBlock)
	{
		delete m_pBlock;
		m_pBlock = NULL;
	}

	if (NULL != m_pBlockFactory)
	{
		delete m_pBlockFactory;
		m_pBlockFactory = NULL;
	}

	if (NULL != m_pMap)
	{
		delete m_pMap;
		m_pMap = NULL;
	}

	if (NULL != m_pMapFactory)
	{
		delete m_pMapFactory;
		m_pMapFactory = NULL;
	}

	if (NULL != m_pTimer)
	{
		delete m_pTimer;
		m_pTimer = NULL;
	}
}

void TetrisWidget::refreshEnvSlot()
{
	if (NULL == m_pBlock ||
		NULL == m_pMap)
	{
		return;
	}

	int iResult = m_pBlock->tryToMoveDown();
	if (STATE_END == iResult)
	{
		stopGame();
	}
	else if (STATE_FAIL == iResult)
	{
		m_pMap->merge(*m_pBlock);

		delete m_pBlock;

		m_pBlock = m_pBlockFactory->createNewBlock();
	}	

	emit refreshScoreSignal(m_pMap->calCount());
	update();
}

void TetrisWidget::paintEvent( QPaintEvent * )
{
	QPainter painter(this);

	painter.setPen(Qt::black);
	painter.setBrush(Qt::yellow);
	if (NULL != m_pBlock)
	{
		QList<PosStru> poses;
		m_pBlock->qryEffectiveBlocks(poses);
		PosStru posStru;
		foreach(posStru, poses)
		{
			painter.drawRect(posStru.iX * BLOCK_SIZE, height() - (posStru.iY + 1) * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
			//painter.fillRect(posStru.iX * BLOCK_SIZE, height() - (posStru.iY + 1) * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, Qt::Dense6Pattern);
		}
	}

	if (NULL != m_pMap)
	{
		QList<PosStru> poses;
		m_pMap->qryEffectiveBlocks(poses);
		PosStru posStru;
		foreach(posStru, poses)
		{
			painter.drawRect(posStru.iX * BLOCK_SIZE, height() - (posStru.iY + 1) * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
			//painter.fillRect(posStru.iX * BLOCK_SIZE, height() - (posStru.iY + 1) * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, Qt::SolidPattern);
		}
	}

	painter.setBrush(Qt::NoBrush);
	painter.drawRect(0,0,width() - 1,height() - 1 );
}

void TetrisWidget::keyPressEvent( QKeyEvent * event )
{
	if (NULL == m_pBlock)
	{
		return;
	}
	switch (event->key())
	{
	case Qt::Key_Left:
		{
			m_pBlock->tryToMoveLeft();
		}
		break;
	case Qt::Key_Right:
		{
			m_pBlock->tryToMoveRight();
		}
		break;
	case Qt::Key_Up:
		{
			m_pBlock->tryToRotateAntiClockWise();
		}
		break;
	case Qt::Key_Down:
		{
			m_pBlock->tryToRotateClockWise();
		}
		break;
	case Qt::Key_A:
		{
			m_pBlock->tryToMoveLeft();
		}
		break;
	case Qt::Key_D:
		{
			m_pBlock->tryToMoveRight();
		}
		break;
	case Qt::Key_W:
		{
			m_pBlock->tryToRotateAntiClockWise();
		}
		break;
	case Qt::Key_S:
		{
			m_pBlock->tryToRotateClockWise();
		}
		break;
	default:
		{

		}
		break;
	}
}

void TetrisWidget::startGame()
{
	if (NULL == m_pMap)
	{
		return;
	}

	if (NULL == m_pBlockFactory)
	{
		return;
	}
	
	if (NULL != m_pBlock)
	{
		delete m_pBlock;
		m_pBlock = NULL;
	}

	m_pBlock = m_pBlockFactory->createNewBlock();

	if (NULL == m_pBlock)
	{
		return;
	}

	m_pMap->start();

	m_pTimer->start(500);
}

void TetrisWidget::stopGame()
{
	m_pTimer->stop();

	emit stopGameSignal();
}


