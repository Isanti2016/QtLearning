#include <QDebug>
#include "QCalculatoruUI.h"


QCalculatorUI::QCalculatorUI() : QWidget(NULL, Qt::WindowCloseButtonHint)
{

}

void QCalculatorUI::OnClickButtonDown()
{
    QPushButton* pButton = (QPushButton*)sender();
    if(NULL != pButton)
    {
        QString strClickText = pButton->text();
        QString strEdit = m_edit->text();
        if( strClickText == "<-")
        {
            if(strEdit.length() > 0)
            {
                strEdit.remove( strEdit.length() - 1, 1);
            }
        }
        else if(strClickText == "C")
        {
            strEdit.clear();
        }
        else if(strClickText == "=")
        {

        }
        else
        {
            strEdit += strClickText;
        }
        m_edit->setText(strEdit);
        //qDebug() << pButton->text()<<endl;
    }
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
         "1", "2", "3", "*", "<-",
         "0", ".", "=", "/", "C"
     };

    m_edit = new QLineEdit(this);
    if( m_edit != NULL )
    {
        m_edit->resize(240, 30);
        m_edit->move(10, 10);
        m_edit->setReadOnly(true);
        m_edit->setAlignment(Qt::AlignRight);
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
                connect( m_button[ i * 5 +j],SIGNAL(clicked()), this, SLOT(OnClickButtonDown()) );
            }
            else
            {
                bRes = false;
            }
        }
    }
    return bRes;
}
