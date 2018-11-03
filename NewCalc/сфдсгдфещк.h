#pragma once

#include <QtWidgets/QWidget>
#include <QPushButton>

class NewCalc : public QWidget
{
	Q_OBJECT

public:
	NewCalc(QWidget *parent = Q_NULLPTR);

private:
	QPushButton *createButton(const QString text, const char *member);

};
