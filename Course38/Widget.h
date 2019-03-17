#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "MyPushButton.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    CMyPushButton m_myButton;
protected slots:
    void OnMyButtonClicked();

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:

};

#endif // WIDGET_H
