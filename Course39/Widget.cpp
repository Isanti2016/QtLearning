#include "Widget.h"
#include <QDebug>
#include <QKeyEvent>


Widget::Widget(QWidget *parent) :
    QWidget(parent), m_MyLineEdit(this)
{
    m_MyLineEdit.installEventFilter(this);

}

Widget::~Widget()
{

}

bool Widget::event(QEvent *e)
{
    if(e->type() == QEvent::KeyPress)
    {
         qDebug() <<"Widget::event(QEvent *e)";
    }

    return QWidget::event(e);
}

void Widget::keyPressEvent(QKeyEvent *e)
{
   qDebug() <<"Widget::keyPressEvent(QKeyEvent *e)";
}

bool Widget::eventFilter(QObject *obj, QEvent* e)
{
    bool bRes = true;
    if((obj == &m_MyLineEdit) && (e->type() == QEvent::KeyPress) )
    {
        qDebug()<< "Widget::eventFilter(QObject *obj, QEvent *e)";

        QKeyEvent* evt = dynamic_cast<QKeyEvent*>(e);

        switch (evt->key())
        {
        case Qt::Key_0:
        case Qt::Key_1:
        case Qt::Key_2:
        case Qt::Key_3:
        case Qt::Key_4:
        case Qt::Key_5:
        case Qt::Key_6:
        case Qt::Key_7:
        case Qt::Key_8:
        case Qt::Key_9:
            bRes = false;
            break;
        default:
            break;
        }
    }
    else
    {
        bRes = QWidget::eventFilter(obj, e);
    }
   return bRes;
}
