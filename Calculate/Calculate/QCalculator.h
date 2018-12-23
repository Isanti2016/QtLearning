#ifndef _QCALCULATOR_H_
#define _QCALCULATOR_H_

#include "QCalculatorDec.h"
#include "QCalculatoruUI.h"


class QCalculator
{
public:
    ~QCalculator();
    static QCalculator *NewIntance();
    void show();

private:
    QCalculatorDec  m_CalculatorDec;
    QCalculatorUI*  m_CalculatorUi;
    bool Construct();
    QCalculator();
};

#endif // QCALCULATOR_H
