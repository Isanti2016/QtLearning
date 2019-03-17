#include "MyLineEdit.h"
#include <QEvent>
#include <QDebug>
#include <QKeyEvent>

CMyLineEdit::CMyLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
}

//重写函数
bool CMyLineEdit::event(QEvent *e)
{
   if(e->type() == QEvent::KeyPress)
   {
       qDebug()<<"CMyLineEdit::event(QEvent *e)";
   }
   return QLineEdit::event(e);
}

void CMyLineEdit::keyPressEvent(QKeyEvent *e)
{
    qDebug()<<"CMyLineEdit::keyPressEvent(QKeyEvent *e)";
    QLineEdit::keyPressEvent(e);

    //e->ignore();
}
