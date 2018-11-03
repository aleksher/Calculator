#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QToolButton>
class QLineEdit;

class Button;

class Calculator : public QWidget
{
	Q_OBJECT

public:
	Calculator(QWidget *parent = 0);

private:
	double savedValue;
	double sumSoFar;
	double factorSoFar;
	QString pendingAdditiveOperator;
	QString pendingMultiplicativeOperator;
	bool waitingForOperand;

	Button* createButton(const QString &text, const char *member);
	void abortOperation();
	bool calculate(double rightOperand, const QString &pendingOperator);



	QLineEdit *display;

	enum { NumDigitButtons = 10 };
	Button *digitButtons[NumDigitButtons];

private slots:
	void digitClicked();
	void additiveOperatorClicked();
	void multiplicativeOperatorClicked();
	void equalClicked();
	void pointClicked();
	void clear();
	void clearAll();
	void readMemory();
	void addToMemory();

};

#endif