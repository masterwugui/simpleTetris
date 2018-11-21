#include "simpletetris.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SimpleTetris w;
	w.show();
	return a.exec();
}
