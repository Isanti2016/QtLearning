#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QObject>
#include <QPushButton>

typedef void (QButtonListener)(QObject*, QMouseEvent*);

class CMyPushButton : public QPushButton
{
    Q_OBJECT

protected:
    QButtonListener* m_listener;

public:
    explicit CMyPushButton(QWidget* parent = 0, QButtonListener* listener = 0);

    //重写
    void mouseReleaseEvent(QMouseEvent *e);
};

#endif // MYPUSHBUTTON_H
