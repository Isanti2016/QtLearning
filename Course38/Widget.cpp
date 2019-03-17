#include "Widget.h"
#include <QDebug>

void OnMyButttonMouseRelease(QObject* sender, QMouseEvent* e)
{
    qDebug()<<"OnMyButttonMouseRelease(QObject* sender, QMouseEvent* e)";
}

Widget::Widget(QWidget *parent)
    : QWidget(parent), m_myButton(this, OnMyButttonMouseRelease)
{
    m_myButton.setText("QMyPushButton");
    connect(&m_myButton, SIGNAL(clicked()), this, SLOT(OnMyButtonClicked()));
}

Widget::~Widget()
{

}

void Widget::OnMyButtonClicked()
{
    qDebug()<< "Widget::OnMyButtonClicked()";
}

