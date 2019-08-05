#include "MainWindow.h"
#include <QMenu>
#include <QStatusBar>
#include <QPalette>


MainWindow::MainWindow():
    m_pFindDlg(new FindDialog(this, &m_objMainEditor)),
    m_strPath(""),
    m_isTextChanged(false),
    m_pReplaceDlg(new ReplaceDialog(this, &m_objMainEditor))
{
    setWindowTitle("NotePad - [ New ]");
    m_strPath = "";
    m_isTextChanged = false;

    setAcceptDrops(true);   //支持拖放
}

bool MainWindow::construct()
{
    bool bRes = true;

    bRes = bRes && initMenuBar();
    bRes = bRes && initToolBar();
    bRes = bRes && initStatusBar();
    bRes = bRes && initMainEditor();


    return bRes;
}

bool MainWindow::initMenuBar()
{
    bool bRes = true;
    QMenuBar* pMb = menuBar();

    bRes = bRes && initFileMenu(pMb);
    bRes = bRes && initEditMenu(pMb);
    bRes = bRes && initFormatMenu(pMb);
    bRes = bRes && initViewMenu(pMb);
    bRes = bRes && initHelpMenu(pMb);

    return bRes;
}

bool MainWindow::initToolBar()
{
    bool bRes = true;
    QToolBar* pTb = addToolBar("Tool Bar");
    pTb->setIconSize(QSize(16, 16));

    bRes = bRes && initFileToolItem(pTb);
    pTb->addSeparator();

    bRes = bRes && initEditorToolItem(pTb);
    pTb->addSeparator();

    bRes = bRes && initFormatToolItem(pTb);
    pTb->addSeparator();

    bRes = bRes && initViewToolItem(pTb);

    return bRes;
}

bool MainWindow::initStatusBar()
{
    bool bRes = true;
    QStatusBar* pSb = statusBar();

    QLabel* pLabel = new QLabel(this);

    if(NULL != pLabel)
    {
       m_objStatusLabel.setMinimumWidth(80);
       m_objStatusLabel.setAlignment(Qt::AlignCenter);
       m_objStatusLabel.setText("Ln: 1    Col:1");

       pLabel->setMinimumWidth(80);
       pLabel->setAlignment(Qt::AlignCenter);
       pLabel->setText("W.bb");

       pSb->addPermanentWidget(&m_objStatusLabel);
       pSb->addPermanentWidget(pLabel);

    }
    else
    {
        bRes = false;
    }

    return bRes;
}

bool MainWindow::initMainEditor()
{
    bool bRes = true;
    m_objMainEditor.setParent(this);
    //设置非激活态，字体高亮颜色
    QPalette ptColor = m_objMainEditor.palette();
    ptColor.setColor(QPalette::Inactive, QPalette::Highlight, ptColor.color(QPalette::Active, QPalette::Highlight));
    ptColor.setColor(QPalette::Inactive, QPalette::HighlightedText, ptColor.color(QPalette::Active, QPalette::HighlightedText));
    m_objMainEditor.setPalette(ptColor);

    connect(&m_objMainEditor, SIGNAL(textChanged()), this, SLOT(OnTextChanged()));              //状态改变

    connect(&m_objMainEditor, SIGNAL(copyAvailable(bool)), this, SLOT(OnCopyAvailable(bool)));  //复制
    connect(&m_objMainEditor, SIGNAL(undoAvailable(bool)), this, SLOT(OnUndoAvailable(bool)));  //重做
    connect(&m_objMainEditor, SIGNAL(redoAvailable(bool)), this, SLOT(OnRedoAvailable(bool)));  //撤销

    connect(&m_objMainEditor, SIGNAL(cursorPositionChanged()), this, SLOT(OnCursorPositionChange())); //光标


    setCentralWidget(&m_objMainEditor);
    return bRes;
}

bool MainWindow::initFileMenu(QMenuBar *pMb)
{
    bool bRes = false;
    QMenu* pMenu = new QMenu("File(&F)", pMb);
    if(NULL == pMenu)
    {
        return bRes;
    }

    bRes = true;
    if(bRes)
    {
        QAction* pAction = NULL;
        bRes = bRes && makeAction(pAction, pMb, "New(&N)", Qt::CTRL + Qt::Key_N);
        if(bRes)
        {
            pMenu->addAction(pAction);
            connect(pAction, SIGNAL(triggered()), this, SLOT(OnFileNew()) );
        }
        pMenu->addSeparator();

        bRes = bRes && makeAction(pAction, pMb, "Open(&O)", Qt::CTRL + Qt::Key_O);
        if(bRes)
        {
            pMenu->addAction(pAction);
            connect(pAction, SIGNAL(triggered()), this, SLOT(OnFileOpen()) );
        }
        pMenu->addSeparator();

        bRes = bRes && makeAction(pAction, pMb, "Save(&S)", Qt::CTRL + Qt::Key_S);
        if(bRes)
        {
            pMenu->addAction(pAction);
            connect( pAction, SIGNAL(triggered()), this, SLOT(OnFileSave()) );
        }
        pMenu->addSeparator();

        bRes = bRes && makeAction(pAction, pMb, "Save As(&A)", Qt::CTRL + Qt::Key_A);
        if(bRes)
        {
            pMenu->addAction(pAction);
            connect( pAction, SIGNAL(triggered()), this, SLOT(OnFileSavaAs()) );
        }
        pMenu->addSeparator();

        bRes = bRes && makeAction(pAction, pMb, "Print(&P)", Qt::CTRL + Qt::Key_P);
        if(bRes)
        {
            connect( pAction, SIGNAL(triggered()), this, SLOT(OnFilePrinter()));
            pMenu->addAction(pAction);
        }
        pMenu->addSeparator();

        bRes = bRes && makeAction(pAction, pMb, "Exit(X)", Qt::CTRL + Qt::Key_X);
        if(bRes)
        {
            connect(pAction, SIGNAL(triggered()), this, SLOT(OnFileExit()));
            pMenu->addAction(pAction);
        }
    }
    if(bRes)
    {
        pMb->addMenu(pMenu);
    }
    else
    {
        delete pMenu;
        pMenu = NULL;
    }
    return bRes;

}

bool MainWindow::initEditMenu(QMenuBar *pMb)
{
    QMenu* pMenu = new QMenu("Edit(&E)", pMb);

    bool bRes = true;
    if(NULL != pMenu)
    {
        QAction* pAction = NULL;

        bRes = bRes && makeAction(pAction, pMb, "Undo(&U)", Qt::CTRL + Qt::Key_U);
        if(bRes)
        {
            connect( pAction, SIGNAL(triggered()), &m_objMainEditor, SLOT(undo()) );
            pAction->setEnabled(false);
            pMenu->addAction(pAction);
        }
        pMenu->addSeparator();

        bRes = bRes && makeAction(pAction, pMb, "Redo(&R)", Qt::CTRL + Qt::Key_R);
        if(bRes)
        {
            connect( pAction, SIGNAL(triggered()), &m_objMainEditor, SLOT(redo()) );
            pAction->setEnabled(false);
            pMenu->addAction(pAction);
        }
        pMenu->addSeparator();

        bRes = bRes && makeAction(pAction, pMb, "Cut(&T)", Qt::CTRL + Qt::Key_T);
        if(bRes)
        {
            connect( pAction, SIGNAL(triggered()), &m_objMainEditor, SLOT(cut()) );
            pAction->setEnabled(false);
            pMenu->addAction(pAction);
        }
        pMenu->addSeparator();

        bRes = bRes && makeAction(pAction, pMb, "Copy(&C)", Qt::CTRL + Qt::Key_C);
        if(bRes)
        {
            connect( pAction, SIGNAL(triggered()), &m_objMainEditor, SLOT(copy()) );
            pAction->setEnabled(false);
            pMenu->addAction(pAction);
        }
        pMenu->addSeparator();

        bRes = bRes && makeAction(pAction, pMb, "Paste(&P)", Qt::CTRL + Qt::Key_P);
        if(bRes)
        {
            connect( pAction, SIGNAL(triggered()), &m_objMainEditor, SLOT(paste()) );
            pMenu->addAction(pAction);
        }
        pMenu->addSeparator();

        bRes = bRes && makeAction(pAction, pMb, "Delete(&D)", Qt::CTRL + Qt::Key_D);
        if(bRes)
        {
            connect(pAction, SIGNAL(triggered()), this, SLOT(OnEditDelete()));
            pMenu->addAction(pAction);
        }
        pMenu->addSeparator();

        bRes = bRes && makeAction(pAction, pMb, "Find(&F)...", Qt::CTRL + Qt::Key_F);
        if(bRes)
        {
            connect(pAction, SIGNAL(triggered()), this, SLOT(OnEditFind()) );
            pMenu->addAction(pAction);
        }
        pMenu->addSeparator();

        bRes = bRes && makeAction(pAction, pMb, "Replace(&R)...", Qt::CTRL + Qt::Key_R);
        if(bRes)
        {
            connect(pAction, SIGNAL(triggered()), this, SLOT(OnEditReplace()));
            pMenu->addAction(pAction);
        }
        pMenu->addSeparator();

        bRes  = bRes && makeAction(pAction, pMb, "Goto(&G)...", Qt::CTRL + Qt::Key_G);
        if(bRes)
        {
            connect(pAction, SIGNAL(triggered(bool)), this, SLOT(OnEditGoto()) );
            pMenu->addAction(pAction);
        }
        pMenu->addSeparator();

        bRes = bRes && makeAction(pAction, pMb, "Select All(&A)", Qt::CTRL + Qt::Key_A);
        if(bRes)
        {
            connect( pAction, SIGNAL(triggered()), &m_objMainEditor, SLOT(selectAll()) );
            pMenu->addAction(pAction);
        }
    }

    if(bRes)
    {
        pMb->addMenu(pMenu);
    }
    else
    {
        delete pMenu;
        pMenu = NULL;
    }
    return bRes;
}

bool MainWindow::initFormatMenu(QMenuBar *pMb)
{
    QMenu* pMenu = new QMenu("Format(&O)", pMb);

    bool bRes = true;
    if(NULL != pMenu)
    {
        QAction* pAction = NULL;

        bRes = bRes && makeAction(pAction, pMb, "Auto Wrap(&W)", Qt::CTRL + Qt::Key_W);
        if(bRes)
        {
            pAction->setCheckable( true );
            pAction->setChecked( true );
            connect( pAction, SIGNAL(triggered(bool)), this, SLOT(OnFormatWrap()) );
            pMenu->addAction(pAction);
        }
        pMenu->addSeparator();

        bRes = bRes && makeAction(pAction, pMb, "Font(&F)...", Qt::CTRL+ Qt::SHIFT + Qt::Key_F );
        if(bRes)
        {
            connect( pAction, SIGNAL(triggered(bool)), this, SLOT(OnFormatFont()) );
            pMenu->addAction(pAction);
        }

    }

    if(bRes)
    {
        pMb->addMenu(pMenu);
    }
    else
    {
        delete pMenu;
        pMenu = NULL;
    }
    return bRes;
}

bool MainWindow::initViewMenu(QMenuBar *pMb)
{
    QMenu* pMenu = new QMenu("View(&V)", pMb);

    bool bRes = true;
    if(NULL != pMenu)
    {
        QAction* pAction = NULL;

        bRes = bRes && makeAction(pAction, pMb, "Tool Bar(&T)", Qt::CTRL + Qt::SHIFT + Qt::Key_T);
        if(bRes)
        {
            pAction->setCheckable(true);
            pAction->setChecked(true);
            connect(pAction, SIGNAL(triggered()), this, SLOT(OnViewToolBar()));
            pMenu->addAction(pAction);
        }

        bRes = bRes && makeAction(pAction, pMb, "Status Bar(&S)", Qt::CTRL + Qt::SHIFT + Qt::Key_S);
        if( bRes )
        {
            pAction->setCheckable(true);
            pAction->setChecked(true);
            connect(pAction, SIGNAL(triggered()), this, SLOT(OnViewStatusBar()));
            pMenu->addAction(pAction);
        }

    }

    if(bRes)
    {
        pMb->addMenu(pMenu);
    }
    else
    {
        delete pMenu;
        pMenu = NULL;
    }
    return bRes;
}

bool MainWindow::initHelpMenu(QMenuBar *pMb)
{
    QMenu* pMenu = new QMenu("Help(&H)", pMb);

    bool bRes = true;
    if(NULL != pMenu)
    {
        QAction* pAction = NULL;

        bRes = bRes && makeAction(pAction, pMb, "User Manual(&U)", Qt::CTRL + Qt::Key_U);
        if(bRes)
        {
            connect( pAction, SIGNAL(triggered(bool)), this, SLOT(OnHelpManual()) );
            pMenu->addAction(pAction);
        }
        pMenu->addSeparator();

        bRes = bRes && makeAction(pAction, pMb, "About NotePad...", 0);
        if(bRes)
        {
            connect(pAction, SIGNAL(triggered(bool)), this, SLOT(OnHelpAbout()));
            pMenu->addAction(pAction);
        }

    }

    if(bRes)
    {
        pMb->addMenu(pMenu);
    }
    else
    {
        delete pMenu;
        pMenu = NULL;
    }
    return bRes;
}

bool MainWindow::initFileToolItem(QToolBar *pTb)
{
    bool bRes = true;
    QAction* pAction = NULL;

    bRes = bRes && makeAction(pAction, pTb, "New", ":/Res/pic/new.png");
    if(bRes)
    {
        pTb->addAction(pAction);
        connect(pAction, SIGNAL(triggered()), this, SLOT(OnFileNew()) );
    }

    bRes = bRes && makeAction(pAction, pTb, "Open", ":/Res/pic/open.png");
    if(bRes)
    {
        pTb->addAction(pAction);
        connect(pAction, SIGNAL(triggered()), this, SLOT(OnFileOpen()) );
    }

    bRes = bRes && makeAction(pAction, pTb, "Save", ":/Res/pic/save.png");
    if(bRes)
    {
        pTb->addAction(pAction);
        connect( pAction, SIGNAL(triggered()), this, SLOT(OnFileSave()) );
    }

    bRes = bRes && makeAction(pAction, pTb, "Save As", ":/Res/pic/saveas.png");
    if(bRes)
    {
        pTb->addAction(pAction);
        connect( pAction, SIGNAL(triggered()), this, SLOT(OnFileSavaAs()) );
    }

    bRes = bRes && makeAction(pAction, pTb, "Print", ":/Res/pic/print.png");
    if(bRes)
    {
        connect( pAction, SIGNAL(triggered()), this, SLOT(OnFilePrinter()));
        pTb->addAction(pAction);
    }

    return bRes;
}

bool MainWindow::initEditorToolItem(QToolBar *pTb)
{
    bool bRes = true;
    QAction* pAction = NULL;
    bRes = bRes && makeAction(pAction, pTb, "Undo", ":/Res/pic/undo.png");
    if(bRes)
    {
        connect( pAction, SIGNAL(triggered()), &m_objMainEditor, SLOT(undo()) );
        pAction->setEnabled(false);
        pTb->addAction(pAction);
    }

    bRes = bRes && makeAction(pAction, pTb, "Redo", ":/Res/pic/redo.png");
    if(bRes)
    {
        connect( pAction, SIGNAL(triggered()), &m_objMainEditor, SLOT(redo()) );
        pAction->setEnabled(false);
        pTb->addAction(pAction);
    }

    bRes = bRes && makeAction(pAction, pTb, "Cut", ":/Res/pic/cut.png");
    if(bRes)
    {
        connect( pAction, SIGNAL(triggered()), &m_objMainEditor, SLOT(cut()) );
        pAction->setEnabled(false);
        pTb->addAction(pAction);
    }

    bRes = bRes && makeAction(pAction, pTb, "Copy", ":/Res/pic/copy.png");
    if(bRes)
    {
        connect( pAction, SIGNAL(triggered()), &m_objMainEditor, SLOT(copy()) );
        pAction->setEnabled(false);
        pTb->addAction(pAction);
    }

    bRes = bRes && makeAction(pAction, pTb, "Paste", ":/Res/pic/paste.png");
    if(bRes)
    {
        connect( pAction, SIGNAL(triggered()), &m_objMainEditor, SLOT(paste()) );
        pTb->addAction(pAction);
    }

    bRes = bRes && makeAction(pAction, pTb, "Find", ":/Res/pic/find.png");
    if(bRes)
    {
        connect( pAction, SIGNAL(triggered()), this, SLOT(OnEditFind()));
        pTb->addAction(pAction);
    }

    bRes = bRes && makeAction(pAction, pTb, "Replace", ":/Res/pic/replace.png");
    if(bRes)
    {
        connect( pAction, SIGNAL(triggered()), this, SLOT(OnEditReplace()));
        pTb->addAction(pAction);
    }

    bRes = bRes && makeAction(pAction, pTb, "Goto", ":/Res/pic/goto.png");
    if(bRes)
    {
        connect(pAction, SIGNAL(triggered(bool)), this, SLOT(OnEditGoto()) );
        pTb->addAction(pAction);
    }


    return bRes;
}

bool MainWindow::initFormatToolItem(QToolBar *pTb)
{
    bool bRes = true;
    QAction* pAction = NULL;
    bRes = bRes && makeAction(pAction, pTb, "Auto Wrap", ":/Res/pic/wrap.png");
    if(bRes)
    {
        pAction->setCheckable( true );
        pAction->setChecked( true );
        connect( pAction, SIGNAL(triggered(bool)), this, SLOT(OnFormatWrap()) );
        pTb->addAction(pAction);
    }

    bRes = bRes && makeAction(pAction, pTb, "Font", ":/Res/pic/font.png");
    if(bRes)
    {
        connect( pAction, SIGNAL(triggered(bool)), this, SLOT(OnFormatFont()) );
        pTb->addAction(pAction);
    }


    return bRes;
}

bool MainWindow::initViewToolItem(QToolBar *pTb)
{
    bool bRes = true;
    QAction* pAction = NULL;
    bRes = bRes && makeAction(pAction, pTb, "Tool Bar", ":/Res/pic/tool.png");
    if(bRes)
    {
        pAction->setCheckable(true);
        pAction->setChecked(true);
        connect(pAction, SIGNAL(triggered()), this, SLOT(OnViewToolBar()));
        pTb->addAction(pAction);
    }

    bRes = bRes && makeAction(pAction, pTb, "Status Bar", ":/Res/pic/status.png");
    if(bRes)
    {
        pAction->setCheckable(true);
        pAction->setChecked(true);
        connect(pAction, SIGNAL(triggered()), this, SLOT(OnViewStatusBar()));
        pTb->addAction(pAction);
    }


    return bRes;
}

//创建菜单动作
bool MainWindow::makeAction(QAction* &pAction, QWidget* pParent, QString text, int key)
{
    bool bRes = true;

    pAction = new QAction(text, pParent);

    if(pAction != NULL)
    {
        pAction->setShortcut(key);
    }
    else
    {
        bRes = false;
    }

    return bRes;
}

//创建工具栏动作
bool MainWindow::makeAction(QAction *&pAction, QWidget* pParent, QString strTip, QString strIconPath)
{
    bool bRes = true;

    pAction = new QAction("", pParent);

    if(NULL != pAction)
    {
        //设置图标名称
        pAction->setToolTip(strTip);
        pAction->setIcon(QIcon(strIconPath));
    }
    else
    {
        bRes = false;
    }
    return bRes;
}



MainWindow *MainWindow::NewInstance()
{
    MainWindow* ret = new MainWindow();
    if(NULL == ret || !ret->construct())
    {
        delete ret;
        ret = NULL;
    }
    return ret;
}

MainWindow::~MainWindow()
{

}
