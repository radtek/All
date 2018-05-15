#include "toolplatform.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ToolPlatform w;
	w.show();
	return a.exec();
}
