#ifndef WIDGETTEST_H
#define WIDGETTEST_H

#include <QWidget>
#include <QPushButton>


class WidgetTest : public QWidget
{
    Q_OBJECT
public:
    WidgetTest(QWidget *parent = 0);
    ~WidgetTest();

private:
    QPushButton FontDialogBtn;
    QPushButton ProgressDialogBtn;
    QPushButton PrintDialogBtn;

private slots:
     void FrontDialogBtn_Clicked();
     void ProgressDialogBtn_Clicked();
     void PrintDialogBtn_Clicked();

};

#endif // WIDGETTEST_H
