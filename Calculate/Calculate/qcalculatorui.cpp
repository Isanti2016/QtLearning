#include "QcalculatoruUI.h"

QCalculatorUI::QCalculatorUI() : QWidget(NULL, Qt::WindowCloseButtonHint)
{

}

QCalculatorUI *QCalculatorUI::NewInstance()
{
    QCalculatorUI* pRet = new QCalculatorUI;
    if( !(pRet && pRet->Construct()) )
    {
        delete pRet;
        pRet = NULL;
    }
    return pRet;
}

QCalculatorUI::~QCalculatorUI()
{

}

void QCalculatorUI::Show()
{
    QWidget::show();
    setFixedSize(width(),height()); //多平台问题，要做窗口显示后，才能得到高，宽
}

bool QCalculatorUI::Construct()
{
    bool bRes = true;
    const char* chButtonText[20] =
    {
         "7", "8", "9", "+", "(",
         "4", "5", "6", "-", ")",
         "1", "2", "3", "*", "->",
         "0", ".", "=", "/", "C"
     };

    m_edit = new QLineEdit(this);
    if( m_edit != NULL )
    {
        m_edit->resize(240, 30);
        m_edit->move(10, 10);
        m_edit->setReadOnly(true);
    }
    else
    {
        bRes = false;
    }

    for(int i = 0; i < 4 && bRes; ++i)
    {
        for(int j = 0; j < 5 && bRes; ++j)
        {
            m_button[ i * 5 + j] = new QPushButton(this);
            if(m_button [ i * 5 + j ] != NULL)
            {
                m_button[ i * 5 + j]->resize(40, 40);
                m_button[ i * 5 + j]->move( 10 + (10 + 40) * j, 50 + (10 + 40) * i);
                m_button[ i * 5 + j]->setText(chButtonText[i* 5 + j]);
            }
            else
            {
                bRes = false;
            }
        }
    }
    return bRes;
}
