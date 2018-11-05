#include <QtWidgets>
#include "button.h"
#include "calculator.h"

Calculator::Calculator(QWidget *parent)
	: QWidget(parent)
{
	// ������������� ����������
	savedValue = 0;
	result = 0;
	isOperatorClicked = false;
	waitingForRightOperand = false;

	// �������� ���� ������
	output = new QLineEdit("0");
	output->setReadOnly(true);
	output->setAlignment(Qt::AlignRight);
	output->setMaxLength(15);

	// �������� ����� ������
	QFont font = output->font();
	font.setPointSize(font.pointSize() + 15);
	output->setFont(font);

	// �������� ������� ������ ����
	for (int i = 0; i < 10; i++) 
	{
		digitButtons[i] = createButton(QString::number(i), SLOT(digitClicked()));
	}
	// �������� ����������� ������
	Button *pointButton = createButton(".", SLOT(pointClicked()));

	Button *clearButton = createButton("Clear", SLOT(clear()));
	Button *clearAllButton = createButton("Clear All", SLOT(clearAll()));

	Button *addToMemoryButton = createButton("M+", SLOT(addToMemory()));
	Button *readMemoryButton = createButton("MR", SLOT(readMemory()));

	Button *divisionButton = createButton("/", SLOT(operatorClicked()));
	Button *multButton = createButton("*", SLOT(operatorClicked()));
	Button *minusButton = createButton("-", SLOT(operatorClicked()));
	Button *plusButton = createButton("+", SLOT(operatorClicked()));
	Button *equalButton = createButton("=", SLOT(equalClicked()));

	// �������� �������� ��������
	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->setSizeConstraint(QLayout::SetFixedSize);

	// ��������� ����������� ������
	// 0 - ����� ������, 0 - ����� �������, 
	// 1 - �� ������� ����� ���������?, 6 - �� ������� �������� ���������
	mainLayout->addWidget(output, 0, 0, 1, 6);
	mainLayout->addWidget(clearButton, 1, 0, 1, 2);
	mainLayout->addWidget(clearAllButton, 1, 3, 1, 2);
	mainLayout->addWidget(addToMemoryButton, 2, 0, 2, 1);
	mainLayout->addWidget(readMemoryButton, 4, 0, 2, 1);

	// ��������� ����������
	for (int i = 1; i < 10; ++i) {
		int row = ((9 - i) / 3) + 2;
		int column = ((i - 1) % 3) + 1;
		mainLayout->addWidget(digitButtons[i], row, column);
	}

	mainLayout->addWidget(digitButtons[0], 5, 1);
	mainLayout->addWidget(pointButton, 5, 2);
	mainLayout->addWidget(divisionButton, 2, 4);
	mainLayout->addWidget(multButton, 3, 4);
	mainLayout->addWidget(minusButton, 4, 4);
	mainLayout->addWidget(plusButton, 5, 4);
	mainLayout->addWidget(equalButton, 5, 3);
	setLayout(mainLayout);

	setWindowTitle("Calculator");
}

void Calculator::digitClicked()
{
	// ������� ������� ������ ����
	Button *clickedButton = qobject_cast<Button *>(sender());
	// ������� ������� �����
	int digitValue = clickedButton->text().toInt();
	// ���� �� ��� ����� �������� - ���������� ���� �����
	if (!isOperatorClicked)
	{
		if (output->text() == "0")
			output->setText(QString::number(digitValue));
		else
			output->setText(output->text() + QString::number(digitValue));
	}
	else
	{
		// ���� ����� �������� - ��������� ������ �������
		if (!waitingForRightOperand)
		{
			output->setText(QString::number(digitValue));
			waitingForRightOperand = true;
		}
		// ���������� ���� ������ ��������
		else
			output->setText(output->text() + QString::number(digitValue));
	}
}

void Calculator::operatorClicked()
{
	if (!isOperatorClicked)
	{
		Button *clickedButton = qobject_cast<Button *>(sender());
		lastOperator = clickedButton->text();
		leftOperand = output->text().toDouble();
		output->clear();
		isOperatorClicked = true;
	}
	else
	{
		rightOperand = output->text().toDouble();
		calculate();
		output->setText(QString::number(result));
		isOperatorClicked = false;
	}
}

void Calculator::equalClicked()
{
	if (!isOperatorClicked)
		output->setText(QString::number(result));
	else
	{
		rightOperand = output->text().toInt();
		calculate();
		output->setText(QString::number(result));
		isOperatorClicked = false;
	}
	leftOperand = rightOperand = 0;

}

void Calculator::calculate()
{
	if (lastOperator == "+")
	{
		result = leftOperand + rightOperand;
	}
	else if (lastOperator == "-")
	{
		result = leftOperand - rightOperand;
	}
	else if (lastOperator == "*")
	{
		result = leftOperand * rightOperand;
	}
	else if (lastOperator == "/")
	{
		if (rightOperand == 0.0)
		{
			clearAll();
			output->setText("Impossible");
		}
		else
			result = leftOperand / rightOperand;
	}
}

void Calculator::pointClicked()
{
	if (!output->text().contains('.'))
		output->setText(output->text() + ".");
}

void Calculator::clear()
{
	output->setText("0");
	if (!isOperatorClicked)
		leftOperand = 0;
	else
		rightOperand = 0;
}

void Calculator::clearAll()
{
	result = 0;
	leftOperand = 0;
	rightOperand = 0;
	output->setText("0");
}


void Calculator::readMemory()
{
	output->setText(QString::number(savedValue));
}

void Calculator::addToMemory()
{
	savedValue = output->text().toDouble();
}

Button *Calculator::createButton(const QString &text, const char *member)
{
	Button *button = new Button(text);
	connect(button, SIGNAL(clicked()), this, member);
	return button;
}