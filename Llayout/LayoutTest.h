#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QStackedLayout>

class CLayoutTest : public QWidget
{
    Q_OBJECT

public:
    CLayoutTest(QWidget* parent = 0);
    ~CLayoutTest();
private:
    QPushButton m_objPreBtn;
    QPushButton m_objNextBtn;
    QLabel m_Lable1;
    QLabel m_Lable2;
    QLabel m_Lable3;
    QLabel m_Lable4;
    QLineEdit m_lineEdit;
    QPushButton m_objBtn1;
    QPushButton m_objBtn2;

    QStackedLayout m_objsLayout;


    void initControl();
    QWidget* Get1stPate();
    QWidget* Get2ndPate();
    QWidget* Get3rdPate();
private slots:
    void onPreBtnClicked();
    void onNextBtnClicked();

};

#endif // MAINWINDOW_H
