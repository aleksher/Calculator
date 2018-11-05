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
	// сохраненное значение
	double savedValue;

	// результат вычислений
	double result;

	// левый операнд
	double leftOperand;

	// правый операнд
	double rightOperand;

	// последний нажатый оператор
	QString lastOperator;

	// был ли нажат оператор
	bool isOperatorClicked;
	bool waitingForRightOperand;
	// создание кнопки
	Button* createButton(const QString &text, const char *member);

	// вычислить значение
	void calculate();

	// окно вывода
	QLineEdit *output;

	// массив кнопок
	Button *digitButtons[10];

private slots:
	// Методы, реагирующие на нажатия кнопок
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