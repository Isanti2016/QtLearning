#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QObject>
#include <QEvent>
#include "MyLineEdit.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

    CMyLineEdit m_MyLineEdit;

public:
    Widget(QWidget* parent = 0);
    ~Widget();

    bool event(QEvent* e);
    void keyPressEvent(QKeyEvent* e);
    bool eventFilter(QObject* obj, QEvent* e);
};

#endif // WIDGET_H
