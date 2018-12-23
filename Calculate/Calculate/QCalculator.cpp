#include "QCalculator.h"

QCalculator::QCalculator()
{

}

QCalculator::~QCalculator()
{
    delete m_CalculatorUi;
    m_CalculatorUi = NULL;
}

QCalculator *QCalculator::NewIntance()
{
    QCalculator* pCalculator = new QCalculator;
    if( pCalculator == NULL || !pCalculator->Construct())
    {
        delete pCalculator;
        pCalculator = NULL;
    }
    return pCalculator;
}

void QCalculator::show()
{
    m_CalculatorUi->show();
}

bool QCalculator::Construct()
{
    bool bRes = false;
    m_CalculatorUi = QCalculatorUI::NewInstance();
    if(NULL != m_CalculatorUi)
    {
        m_CalculatorUi->SetCalculator( &m_CalculatorDec );
        bRes = true;
    }
    return bRes;
}
