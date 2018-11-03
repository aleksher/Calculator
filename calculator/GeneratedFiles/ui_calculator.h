/********************************************************************************
** Form generated from reading UI file 'calculator.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALCULATOR_H
#define UI_CALCULATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_calculatorClass
{
public:

    void setupUi(QWidget *calculatorClass)
    {
        if (calculatorClass->objectName().isEmpty())
            calculatorClass->setObjectName(QStringLiteral("calculatorClass"));
        calculatorClass->resize(600, 400);

        retranslateUi(calculatorClass);

        QMetaObject::connectSlotsByName(calculatorClass);
    } // setupUi

    void retranslateUi(QWidget *calculatorClass)
    {
        calculatorClass->setWindowTitle(QApplication::translate("calculatorClass", "calculator", nullptr));
    } // retranslateUi

};

namespace Ui {
    class calculatorClass: public Ui_calculatorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALCULATOR_H
