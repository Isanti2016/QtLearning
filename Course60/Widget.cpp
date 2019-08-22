#include "Widget.h"
#include "DataSource.h"
#include <QMessageBox>
#include <QString>
#include <QAction>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    InitCtrl();
    ConnectSlots();

    //按照过滤器
    m_TableView.installEventFilter(this);

    m_ScoreModel.SetView( m_TableView );
    OnRefreshBtnClicked();
}

Widget::~Widget()
{

}

void Widget::InitCtrl()
{
    m_TableView.setParent(this);
    m_TableView.move(10, 10);
    m_TableView.resize( 350, 200 );

    m_RefreshBtn.setParent(this);
    m_RefreshBtn.move( 10, 220 );
    m_RefreshBtn.resize( 90, 30 );
    m_RefreshBtn.setText( "Refresh" );


    m_ClearBtn.setParent(this);
    m_ClearBtn.move( 140, 220 );
    m_ClearBtn.resize( 90, 30 );
    m_ClearBtn.setText( "Clear" );


    m_ScoreBtn.setParent(this);
    m_ScoreBtn.move( 270, 220 );
    m_ScoreBtn.resize( 90, 30 );
    m_ScoreBtn.setText( "Calc" );

    m_menu.addAction("Delete");
}

void Widget::ConnectSlots()
{
    connect( &m_RefreshBtn, SIGNAL(clicked(bool)), this, SLOT(OnRefreshBtnClicked()) );
    connect( &m_ClearBtn, SIGNAL(clicked(bool)), this, SLOT(OnClearBtnClicked()) );
    connect( &m_ScoreBtn, SIGNAL(clicked(bool)), this, SLOT(OnScoreBtnClicked()) );

    connect( m_menu.actions()[0], SIGNAL(triggered(bool)), this, SLOT(OnDeleteClicked()) );
}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if( (watched == &m_TableView) && (event->type() == QEvent::ContextMenu) )
    {
        //显示右键
        m_menu.exec( cursor().pos() );
    }

    //要调用基类的函数返回处理结果
    return QWidget::eventFilter(watched, event);
}

void Widget::OnRefreshBtnClicked()
{
    //先清空下数据
    OnClearBtnClicked();

    DataSource objDataSrc;
    if( objDataSrc.SetPath( "G:/C++/Qtlearning/Course60/Text.txt" ) )
    {
        if( !m_ScoreModel.Add( objDataSrc.fetchData() ) )
        {
            QMessageBox::critical(this, "Error", "Add Data to Model Error", QMessageBox::Ok);
        }
    }
    else
    {
        QMessageBox::critical(this, "Error", "Data Source Read Error", QMessageBox::Ok);
    }
}

void Widget::OnClearBtnClicked()
{
    m_ScoreModel.Clear();
}

void Widget::OnScoreBtnClicked()
{
    int iMin = 256;
    int iMax = -1;
    int iAverage = 0;

    if( m_ScoreModel.count() > 0 )
    {
        for( int i=0; i<m_ScoreModel.count(); ++i )
        {
            ScoreInfo info = m_ScoreModel.GetItem(i);

            if( info.Score() < iMin )
            {
                iMin = info.Score();
            }

            if( info.Score() > iMax )
            {
                iMax = info.Score();
            }

            iAverage += info.Score();
        }
        iAverage /= m_ScoreModel.count();

        QMessageBox::information( this, "Statistic", QString().sprintf("Min: %d\nMax: %d\nAverage: %d", iMin, iMax, iAverage), QMessageBox::Ok );
    }
    else
    {
        QMessageBox::information( this, "Statistic","No Data Record!", QMessageBox::Ok );
    }

}

void Widget::OnDeleteClicked()
{
    //删除对应行的数据
    m_ScoreModel.Remove( m_TableView.currentIndex().row() );
}
