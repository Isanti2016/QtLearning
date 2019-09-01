#include "MainWindow.h"
#include <QMenuBar>
#include <QAction>
#include <QColorDialog>
#include <QPainter>
#include <QMouseEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <QImage>
#include <QPixmap>
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>

const int SPECIAL_SHAPE_POINT_SIZE = 2;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(500, 400);
    InitMenu();
    InitToolBar();

    m_stuCurrentDrawPara.Clear();
}

MainWindow::~MainWindow()
{

}

bool MainWindow::InitMenu()
{
    bool bRes = true;
    //1.创建菜单栏
    QMenuBar* pMenuBar = menuBar();

    //2.创建菜单
    QMenu* pMenu = new QMenu("File(&F)", pMenuBar);
    if(pMenuBar != NULL && pMenu != NULL)
    {
        //3.创建菜单中的动作
        QAction* pAction = NULL;
        bRes = bRes && makeAction( pAction, pMenu, "Open File(&O)", Qt::CTRL + Qt::Key_O );
        if(bRes)
        {
            connect( pAction, SIGNAL(triggered(bool)), this, SLOT(OnOpen()) );
        }
        pAction = NULL;
        bRes = bRes && makeAction( pAction, pMenu, "New File(&N)", Qt::CTRL + Qt::Key_N );
        if(bRes)
        {
            connect( pAction, SIGNAL(triggered(bool)), this, SLOT(OnNew()) );
        }
        pAction = NULL;
        bRes = bRes && makeAction( pAction, pMenu, "Save File(&S)", Qt::CTRL + Qt::Key_S );
        if(bRes)
        {
            connect( pAction, SIGNAL(triggered(bool)), this, SLOT(OnSave()) );
        }
        pAction = NULL;

        pMenuBar->addMenu(pMenu);
    }
    else
    {
        bRes = false;
    }


    return bRes;
}

bool MainWindow::InitToolBar()
{
    bool bRes = true;
    //1.添加工具栏
    QToolBar* pToolBar = addToolBar("Tool Bar");
    pToolBar->setIconSize( QSize(16, 16) );

    //2.添加工具栏中的动作
    bRes = bRes && InitFileItem( pToolBar );
    pToolBar->addSeparator();

    bRes = bRes && InitToolItem( pToolBar );
    pToolBar->addSeparator();

    bRes = bRes && InitViewItem( pToolBar );


    return bRes;
}

bool MainWindow::InitFileItem( QToolBar* pToolBar )
{
    bool bRes = true;
    if( pToolBar != NULL )
    {
        //添加工具栏中的动作
        QAction* pAction = NULL;
        bRes = bRes && makeAction( pAction, pToolBar, "Open", ":/Src/open.png" );
        if(bRes)
        {
            connect( pAction, SIGNAL(triggered(bool)), this, SLOT(OnOpen()) );
        }

        pAction = NULL;
        bRes = bRes && makeAction( pAction, pToolBar, "New", ":/Src/new.png" );
        if(bRes)
        {
            connect( pAction, SIGNAL(triggered(bool)), this, SLOT(OnNew()) );
        }

        pAction = NULL;
        bRes = bRes && makeAction( pAction, pToolBar, "Save", ":/Src/save.png" );
        if(bRes)
        {
            connect( pAction, SIGNAL(triggered(bool)), this, SLOT(OnSave()) );
        }

        pAction = NULL;
        bRes = bRes && makeAction( pAction, pToolBar, "Clear", ":/Src/clear.png" );
        if(bRes)
        {
            connect( pAction, SIGNAL(triggered(bool)), this, SLOT(OnClear()) );
        }

        pAction = NULL;
        bRes = bRes && makeAction( pAction, pToolBar, "Capture Screen", ":/Src/capture.png" );
        if(bRes)
        {
            connect( pAction, SIGNAL(triggered(bool)), this, SLOT(OnCaptureScreen()) );
        }

    }
    else
    {
        bRes = false;
    }


    return bRes;
}

bool MainWindow::InitToolItem( QToolBar* pToolBar )
{
    bool bRes = true;
    if( pToolBar != NULL )
    {
        //添加工具栏中的动作
        QAction* pAction = NULL;
        bRes = bRes && makeAction( pAction, pToolBar, "Free", ":/Src/Free.png" );
        if(bRes)
        {
            pAction->setCheckable( true );
            pAction->setChecked( false );
            connect( pAction, SIGNAL(triggered(bool)), this, SLOT(OnShapeFreeType()) );
        }

        pAction = NULL;
        bRes = bRes && makeAction( pAction, pToolBar, "Line", ":/Src/Line.png" );
        if(bRes)
        {
            pAction->setCheckable( true );
            pAction->setChecked( false );
            connect( pAction, SIGNAL(triggered(bool)), this, SLOT(OnShapeLineType()) );
        }

        pAction = NULL;
        bRes = bRes && makeAction( pAction, pToolBar, "Rect", ":/Src/Rect.png" );
        if(bRes)
        {
            pAction->setCheckable( true );
            pAction->setChecked( false );
            connect( pAction, SIGNAL(triggered(bool)), this, SLOT(OnShapeRectType()) );
        }

        pAction = NULL;
        bRes = bRes && makeAction( pAction, pToolBar, "RoundedRect", ":/Src/RoundedRect.png" );
        if(bRes)
        {
            pAction->setCheckable( true );
            pAction->setChecked( false );
            connect( pAction, SIGNAL(triggered(bool)), this, SLOT(OnShapeRoundedRectType()) );
        }

        pAction = NULL;
        bRes = bRes && makeAction( pAction, pToolBar, "Ellipse", ":/Src/Ellipse.png" );
        if(bRes)
        {
            pAction->setCheckable( true );
            pAction->setChecked( false );
            connect( pAction, SIGNAL(triggered(bool)), this, SLOT(OnShapeEllipseType()) );
        }
    }
    else
    {
        bRes = false;
    }

    return bRes;
}

bool MainWindow::InitViewItem( QToolBar* pToolBar )
{
    bool bRes = true;
    if( pToolBar != NULL )
    {
        //添加工具栏中的动作
        QAction* pAction = NULL;
        bRes = bRes && makeAction( pAction, pToolBar, "Color", ":/Src/Color.png" );
        if(bRes)
        {
            connect( pAction, SIGNAL(triggered(bool)), this, SLOT(OnColor()) );
        }
    }
    else
    {
        bRes = false;
    }


    return bRes;
}

bool MainWindow::makeAction( QAction*& pAction, QMenu* pMenu, QString keyTip, int iShortKey )
{
    bool bRes = true;
    pAction = new QAction(keyTip, pMenu);
    if( NULL != pAction && pMenu != NULL)
    {
        pAction->setShortcut( QKeySequence( iShortKey) );

        pMenu->addAction(pAction);
    }
    else
    {
        bRes = false;
    }
    return bRes;
}

bool MainWindow::makeAction( QAction*& pAction, QToolBar* pToolBar, QString keyTip, QString strIconPath )
{
    bool bRes = true;
    pAction = new QAction("", pToolBar);
    if( NULL != pAction && pToolBar != NULL)
    {
        pAction->setToolTip( keyTip );
        pAction->setIcon( QIcon(strIconPath) );

        pToolBar->addAction(pAction);
    }
    else
    {
        bRes = false;
    }
    return bRes;
}

void MainWindow::OnOpen()
{

    QString filename = QFileDialog::getOpenFileName( this, "选择图像", ".", "Images (*.png *.bmp *.jpg)" );
    if( !filename.isEmpty() )
    {
        QImage img;
        if( img.load( filename ) )
        {
            m_pMap = QPixmap::fromImage( img );
            update();
        }
        else
        {
            QMessageBox::critical( this, "Error", "Invaild Image", QMessageBox::Ok );
        }
    }

}

void MainWindow::OnNew()
{
    m_listDrawPara.clear();
    m_stuCurrentDrawPara.Clear();
    m_pMap = QPixmap();

    //清空任何选择的形状
    ChangeShapeTypeEnable( "" );

    update();
}

void MainWindow::OnSave()
{
    QString filename = QFileDialog::getSaveFileName( this, "保存图像", ".", "Images (*.png *.bmp *.jpg)"  );

    if( !filename.isEmpty() )
    {
        if( !m_pMap.isNull() )
        {
           m_pMap.save( filename );
        }
        else
        {
            m_pMap.save(this);
        }
    }

}

void MainWindow::OnClear()
{
    for( int i = 0; i < m_listDrawPara.count(); ++i )
    {
        m_listDrawPara.at(i).m_vecPoint.clear();
    }
    m_stuCurrentDrawPara.m_vecPoint.clear();

    m_pMap = QPixmap();
    update();
}

void MainWindow::OnCaptureScreen()
{
    m_pMap = QPixmap::grabWindow( QApplication::desktop()->winId() );
    update();
}

void MainWindow::OnShapeFreeType()
{
    m_stuCurrentDrawPara.m_enShapeType = EN_Shape_Type_Free;
    ChangeShapeTypeEnable( QString("Free") );
}

void MainWindow::OnShapeLineType()
{
    m_stuCurrentDrawPara.m_enShapeType = EN_Shape_Type_Line;
    ChangeShapeTypeEnable( QString("Line") );
}

void MainWindow::OnShapeRectType()
{
    m_stuCurrentDrawPara.m_enShapeType = EN_Shape_Type_Rect;
    ChangeShapeTypeEnable( QString("Rect") );
}

void MainWindow::OnShapeRoundedRectType()
{
    m_stuCurrentDrawPara.m_enShapeType = EN_Shape_Type_RoundedRect;
    ChangeShapeTypeEnable( QString("RoundedRect") );
}

void MainWindow::OnShapeEllipseType()
{
    m_stuCurrentDrawPara.m_enShapeType = EN_Shape_Type_Ellipse;
    ChangeShapeTypeEnable( QString("Ellipse") );
}

void MainWindow::OnColor()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Color Select", QColorDialog::ShowAlphaChannel);
    if( color.isValid() )
    {
        m_stuCurrentDrawPara.m_color = color;
    }
    else
    {
        m_stuCurrentDrawPara.m_color = Qt::white;
    }
}

void MainWindow::ChangeShapeTypeEnable(const QString& strShapeType)
{
    QToolBar* pToolBar = ToolBar();

    //1.工具栏所有动作使能状态清空
    if( pToolBar != NULL )
    {
        QList<QAction*> listAct = pToolBar->actions();

        for( int i = 0; i < listAct.count(); ++i )
        {
            listAct[i]->setChecked(false);
        }
    }
    //2.设置当前点击的动作使能
    QAction* pAc = FindToolAction( strShapeType );
    if(NULL != pAc )
    {
        pAc->setChecked( true );
    }
}

QAction* MainWindow::FindToolAction( const QString& strShapeType )
{
    QAction* pAc = NULL;
    QToolBar* pToolBar = ToolBar();

    if( pToolBar != NULL )
    {
        QList<QAction*> listAct = pToolBar->actions();

        for( int i = 0; i < listAct.count(); ++i )
        {
            if( listAct[i]->toolTip().startsWith(strShapeType, Qt::CaseInsensitive) )
            {
                pAc = listAct[i];
                break;
            }
        }
    }

    return pAc;
}

QToolBar *MainWindow::ToolBar()
{
    QToolBar* pToolBar = NULL;

    const QObjectList list = children();
    int iCount = list.count();
    for(int i = 0; i < iCount; ++i)
    {
        QToolBar *objTb = dynamic_cast<QToolBar*> (list[i]);
        if( objTb != NULL )
        {
            pToolBar = objTb;
            break;
        }
    }

    return pToolBar;
}

void MainWindow::mousePressEvent(QMouseEvent *evt)
{
    m_stuCurrentDrawPara.m_vecPoint.clear();

    m_stuCurrentDrawPara.m_vecPoint.append( evt->pos() );
}

void MainWindow::mouseMoveEvent(QMouseEvent *evt)
{
    AppendPoint( evt->pos() );

    //刷出轨迹
    update();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *evt)
{
    AppendPoint( evt->pos() );

    //终点
    update();

    m_listDrawPara.append( m_stuCurrentDrawPara );
    m_stuCurrentDrawPara.m_vecPoint.clear();
}

void MainWindow::Draw(QPainter& objPainter, const DrawPara& stuDrawPara)
{
    objPainter.setPen( stuDrawPara.m_color );
    objPainter.setBrush( stuDrawPara.m_color );

    if( (stuDrawPara.m_vecPoint.count() >= SPECIAL_SHAPE_POINT_SIZE) && (stuDrawPara.m_enShapeType != UnKnown) )
    {
        int xMin = ( stuDrawPara.m_vecPoint.at(0).x() < stuDrawPara.m_vecPoint.at(1).x() ) ? stuDrawPara.m_vecPoint.at(0).x() : stuDrawPara.m_vecPoint.at(1).x();
        int yMin = ( stuDrawPara.m_vecPoint.at(0).y() < stuDrawPara.m_vecPoint.at(1).y() ) ? stuDrawPara.m_vecPoint.at(0).y() : stuDrawPara.m_vecPoint.at(1).y();
        int width = qAbs( stuDrawPara.m_vecPoint.at(0).x() - stuDrawPara.m_vecPoint.at(1).x() );
        int height = qAbs( stuDrawPara.m_vecPoint.at(0).y() - stuDrawPara.m_vecPoint.at(1).y() );
        switch ( stuDrawPara.m_enShapeType )
        {
        case EN_Shape_Type_Free:
            for( int i = 0; i < stuDrawPara.m_vecPoint.count() - 1; ++i )
            {
                objPainter.drawLine( stuDrawPara.m_vecPoint.at(i), stuDrawPara.m_vecPoint.at(i+1) );
            }
            break;
        case EN_Shape_Type_Line:
            if( stuDrawPara.m_vecPoint.at(0) != stuDrawPara.m_vecPoint.at(1) )
            {
                objPainter.drawLine( stuDrawPara.m_vecPoint.at(0), stuDrawPara.m_vecPoint.at(1) );
            }
            break;
        case EN_Shape_Type_Rect:
            objPainter.drawRect( xMin, yMin, width, height );
            break;
        case EN_Shape_Type_RoundedRect:
            objPainter.drawRoundRect( xMin, yMin, width, height );
            break;
        case EN_Shape_Type_Ellipse:
            objPainter.drawEllipse( xMin, yMin, width, height );
            break;
        default:
            break;
        }
    }
}

void MainWindow::paintEvent(QPaintEvent *evt)
{
    evt;

    QPainter objPainter( this );

    for( int i = 0; i < m_listDrawPara.count(); ++i )
    {
        Draw( objPainter, m_listDrawPara[i] );
    }
    Draw( objPainter, m_stuCurrentDrawPara );

    //显示图像
    if( !m_pMap.isNull() )
    {
        int iHeight = 0;
        QToolBar* tb = ToolBar();
        if(NULL != tb)
        {
            iHeight = tb->height() * 2;
        }
        objPainter.drawPixmap(0, iHeight, width()-iHeight, height()-iHeight, m_pMap);
    }

}

void MainWindow::AppendPoint(const QPoint &point)
{
    switch (m_stuCurrentDrawPara.m_enShapeType)
    {
    case EN_Shape_Type_Free:
        m_stuCurrentDrawPara.m_vecPoint.append( point );
        break;
    case EN_Shape_Type_Line:
    case EN_Shape_Type_Rect:
    case EN_Shape_Type_RoundedRect:
    case EN_Shape_Type_Ellipse:
        //画这些图形，仅需要两个点
        if( m_stuCurrentDrawPara.m_vecPoint.count() == SPECIAL_SHAPE_POINT_SIZE )
        {
            m_stuCurrentDrawPara.m_vecPoint.removeLast();
        }
        m_stuCurrentDrawPara.m_vecPoint.append( point );
        break;
    default:
        break;
    };
}



