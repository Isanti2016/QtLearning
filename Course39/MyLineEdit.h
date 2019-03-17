#ifndef CMYLINEEDIT_H
#define CMYLINEEDIT_H

#include <QWidget>
#include <QLineEdit>

class CMyLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit CMyLineEdit(QWidget *parent = 0);

    //重写
    bool event(QEvent* e);
    void keyPressEvent(QKeyEvent* e);
};


#endif // CMYLINEEDIT_H
