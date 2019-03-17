#include "MyPushButton.h"
#include <QDebug>

CMyPushButton::CMyPushButton(QWidget* parent, QButtonListener* listener)
    :QPushButton(parent)
{
    m_listener = listener;
}

//重写函数
void CMyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
     if( m_listener != NULL)
     {
         m_listener(this, e);
     }
     else
     {
        QPushButton::mouseReleaseEvent(e);
     }

}
