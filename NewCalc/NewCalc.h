#pragma once

#include <QtWidgets/QWidget>
#include "ui_NewCalc.h"

class NewCalc : public QWidget
{
	Q_OBJECT

public:
	NewCalc(QWidget *parent = Q_NULLPTR);

private:
	Ui::NewCalcClass ui;
};
