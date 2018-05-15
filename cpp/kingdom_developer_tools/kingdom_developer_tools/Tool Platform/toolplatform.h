#ifndef TOOLPLATFORM_H
#define TOOLPLATFORM_H

#include <QtWidgets/QMainWindow>
#include "ui_toolplatform.h"

class ToolPlatform : public QMainWindow
{
	Q_OBJECT

public:
	ToolPlatform(QWidget *parent = 0);
	~ToolPlatform();

private:
	Ui::ToolPlatformClass ui;
};

#endif // TOOLPLATFORM_H
