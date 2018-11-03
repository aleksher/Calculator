#include <QtWidgets>

#include <cmath>

#include "button.h"
#include "calculator.h"

Calculator::Calculator(QWidget *parent)
	: QWidget(parent)
{
	savedValue = 0.0;
	sumSoFar = 0.0;
	factorSoFar = 0.0;
	waitingForOperand = true;

	display = new QLineEdit("0");
	display->setReadOnly(true);
	display->setAlignment(Qt::AlignRight);
	display->setMaxLength(15);

	QFont font = display->font();
	font.setPointSize(font.pointSize() + 8);
	display->setFont(font);

	for (int i = 0; i < NumDigitButtons; ++i) {
		digitButtons[i] = createButton(QString::number(i), SLOT(digitClicked()));
	}

	Button *pointButton = createButton(".", SLOT(pointClicked()));

	Button *clearButton = createButton("Clear", SLOT(clear()));
	Button *clearAllButton = createButton("Clear All", SLOT(clearAll()));

	Button *addToMemoryButton = createButton("M+", SLOT(addToMemory()));
	Button *readMemoryButton = createButton("MR", SLOT(readMemory()));

	Button *divisionButton = createButton("/", SLOT(multiplicativeOperatorClicked()));
	Button *timesButton = createButton("*", SLOT(multiplicativeOperatorClicked()));
	Button *minusButton = createButton("-", SLOT(additiveOperatorClicked()));
	Button *plusButton = createButton("+", SLOT(additiveOperatorClicked()));
	Button *equalButton = createButton("=", SLOT(equalClicked()));

	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->setSizeConstraint(QLayout::SetFixedSize);
	mainLayout->addWidget(display, 0, 0, 1, 6);
	mainLayout->addWidget(clearButton, 1, 0, 1, 2);
	mainLayout->addWidget(clearAllButton, 1, 3, 1, 2);

	mainLayout->addWidget(addToMemoryButton, 2, 0, 2, 1);
	mainLayout->addWidget(readMemoryButton, 4, 0, 2, 1);

	// Установка циферблата
	for (int i = 1; i < NumDigitButtons; ++i) {
		int row = ((9 - i) / 3) + 2;
		int column = ((i - 1) % 3) + 1;
		mainLayout->addWidget(digitButtons[i], row, column);
	}

	mainLayout->addWidget(digitButtons[0], 5, 1);
	mainLayout->addWidget(pointButton, 5, 2);
	mainLayout->addWidget(divisionButton, 2, 4);
	mainLayout->addWidget(timesButton, 3, 4);
	mainLayout->addWidget(minusButton, 4, 4);
	mainLayout->addWidget(plusButton, 5, 4);
	mainLayout->addWidget(equalButton, 5, 3);
	setLayout(mainLayout);

	setWindowTitle("Calculator");
}

void Calculator::digitClicked()
{
	// Получим нажатую кнопку
	Button *clickedButton = qobject_cast<Button *>(sender());
	int digitValue = clickedButton->text().toInt();
	if (display->text() == "0" && digitValue == 0.0)
		return;

	if (waitingForOperand) {
		display->clear();
		waitingForOperand = false;
	}
	display->setText(display->text() + QString::number(digitValue));
}


void Calculator::additiveOperatorClicked()
{
	Button *clickedButton = qobject_cast<Button *>(sender());
	QString clickedOperator = clickedButton->text();
	double operand = display->text().toDouble();

	if (!pendingMultiplicativeOperator.isEmpty()) 
	{
		if (!calculate(operand, pendingMultiplicativeOperator)) 
		{
			abortOperation();
			return;
		}
		display->setText(QString::number(factorSoFar));
		operand = factorSoFar;
		factorSoFar = 0.0;
		pendingMultiplicativeOperator.clear();
	}

	if (!pendingAdditiveOperator.isEmpty()) 
	{
		if (!calculate(operand, pendingAdditiveOperator)) 
		{
			abortOperation();
			return;
		}
		display->setText(QString::number(sumSoFar));
	}
	else 
	{
		sumSoFar = operand;
	}

	pendingAdditiveOperator = clickedOperator;
	waitingForOperand = true;
}

void Calculator::multiplicativeOperatorClicked()
{
	Button *clickedButton = qobject_cast<Button *>(sender());
	QString clickedOperator = clickedButton->text();
	double operand = display->text().toDouble();

	if (!pendingMultiplicativeOperator.isEmpty()) 
	{
		if (!calculate(operand, pendingMultiplicativeOperator)) {
			abortOperation();
			return;
		}
		display->setText(QString::number(factorSoFar));
	}
	else 
	{
		factorSoFar = operand;
	}

	pendingMultiplicativeOperator = clickedOperator;
	waitingForOperand = true;
}

void Calculator::equalClicked()
{
	double operand = display->text().toDouble();

	if (!pendingMultiplicativeOperator.isEmpty()) 
	{
		if (!calculate(operand, pendingMultiplicativeOperator)) {
			abortOperation();
			return;
		}
		operand = factorSoFar;
		factorSoFar = 0.0;
		pendingMultiplicativeOperator.clear();
	}
	if (!pendingAdditiveOperator.isEmpty()) 
	{
		if (!calculate(operand, pendingAdditiveOperator)) 
		{
			abortOperation();
			return;
		}
		pendingAdditiveOperator.clear();
	}
	else {
		sumSoFar = operand;
	}

	display->setText(QString::number(sumSoFar));
	sumSoFar = 0.0;
	waitingForOperand = true;
}

void Calculator::pointClicked()
{
	if (waitingForOperand)
		display->setText("0");
	if (!display->text().contains('.'))
		display->setText(display->text() + ".");
	waitingForOperand = false;
}

void Calculator::clear()
{
	if (waitingForOperand)
		return;

	display->setText("0");
	waitingForOperand = true;
}

void Calculator::clearAll()
{
	sumSoFar = 0.0;
	factorSoFar = 0.0;
	pendingAdditiveOperator.clear();
	pendingMultiplicativeOperator.clear();
	display->setText("0");
	waitingForOperand = true;
}


void Calculator::readMemory()
{
	display->setText(QString::number(savedValue));
	waitingForOperand = true;
}

void Calculator::addToMemory()
{
	equalClicked();
	savedValue += display->text().toDouble();
}
Button *Calculator::createButton(const QString &text, const char *member)
{
	Button *button = new Button(text);
	connect(button, SIGNAL(clicked()), this, member);
	return button;
}

void Calculator::abortOperation()
{
	clearAll();
	display->setText("Impossible");
}

bool Calculator::calculate(double rightOperand, const QString &pendingOperator)
{
	if (pendingOperator == "+") {
		sumSoFar += rightOperand;
	}
	else if (pendingOperator == "-") {
		sumSoFar -= rightOperand;
	}
	else if (pendingOperator == "*") {
		factorSoFar *= rightOperand;
	}
	else if (pendingOperator == "/") {
		if (rightOperand == 0.0)
			return false;
		factorSoFar /= rightOperand;
	}
	return true;
}