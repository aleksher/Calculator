#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
class QLineEdit;

class Button;

class Calculator : public QWidget
{
	Q_OBJECT

public:
	Calculator(QWidget *parent = 0);

private:
	double savedValue;
	double result;
	double leftOperand;
	double rightOperand;
	QString lastOperator;
	bool waitingForOperand;

	Button* createButton(const QString &text, const char *member);
	void calculate();

	QLineEdit *output;

	Button *digitButtons[10];

private slots:
	void digitClicked();
	void operatorClicked();
	void equalClicked();
	void pointClicked();
	void clear();
	void clearAll();
	void readMemory();
	void addToMemory();

};

#endif