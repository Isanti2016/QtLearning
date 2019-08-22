#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QTableView>
#include <QMenu>
#include "Scoreinfomodel.h"


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
private:
        QPushButton m_RefreshBtn;
        QPushButton m_ClearBtn;
        QPushButton m_ScoreBtn;

        QTableView m_TableView;
        ScoreInfoModel m_ScoreModel;

        QMenu m_menu;

        void InitCtrl();
        void ConnectSlots();

        //重写事件过滤器
        bool eventFilter(QObject *watched, QEvent *event);

private slots:
        void OnRefreshBtnClicked();
        void OnClearBtnClicked();
        void OnScoreBtnClicked();

        void OnDeleteClicked();
};

#endif // WIDGET_H
