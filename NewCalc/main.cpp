#include "NewCalc.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	NewCalc w;
	w.show();
	return a.exec();
}
