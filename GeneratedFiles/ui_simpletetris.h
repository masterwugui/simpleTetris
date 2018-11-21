/********************************************************************************
** Form generated from reading UI file 'simpletetris.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMPLETETRIS_H
#define UI_SIMPLETETRIS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SimpleTetrisClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *mainLayout;

    void setupUi(QMainWindow *SimpleTetrisClass)
    {
        if (SimpleTetrisClass->objectName().isEmpty())
            SimpleTetrisClass->setObjectName(QString::fromUtf8("SimpleTetrisClass"));
        SimpleTetrisClass->resize(812, 570);
        centralWidget = new QWidget(SimpleTetrisClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        mainLayout = new QHBoxLayout();
        mainLayout->setSpacing(6);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));

        horizontalLayout_2->addLayout(mainLayout);

        SimpleTetrisClass->setCentralWidget(centralWidget);

        retranslateUi(SimpleTetrisClass);

        QMetaObject::connectSlotsByName(SimpleTetrisClass);
    } // setupUi

    void retranslateUi(QMainWindow *SimpleTetrisClass)
    {
        SimpleTetrisClass->setWindowTitle(QApplication::translate("SimpleTetrisClass", "SimpleTetris", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SimpleTetrisClass: public Ui_SimpleTetrisClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMPLETETRIS_H
