#include "MainWindow.h"
#include <QMenu>
#include <QStatusBar>




MainWindow::MainWindow()
{

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
       objStatusLabel.setMinimumWidth(80);
       objStatusLabel.setAlignment(Qt::AlignCenter);
       objStatusLabel.setText("Ln: 1    Col:1");

       pLabel->setMinimumWidth(80);
       pLabel->setAlignment(Qt::AlignCenter);
       pLabel->setText("W.bb");

       pSb->addPermanentWidget(&objStatusLabel);
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
    objMainEditor.setParent(this);

    setCentralWidget(&objMainEditor);
    return bRes;
}

bool MainWindow::initFileMenu(QMenuBar *pMb)
{
    bool bRes = false;
    QMenu* pMenu = new QMenu("File(&F)");
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
        }
        pMenu->addSeparator();

        bRes = bRes && makeAction(pAction, pMb, "Open(&O)", Qt::CTRL + Qt::Key_O);
        if(bRes)
        {
            pMenu->addAction(pAction);
        }
        pMenu->addSeparator();

        bRes = bRes && makeAction(pAction, pMb, "Save(&S)", Qt::CTRL + Qt::Key_S);
        if(bRes)
        {
            pMenu->addAction(pAction);
        }
        pMenu->addSeparator();

        bRes = bRes && makeAction(pAction, pMb, "Save As(&A)", Qt::CTRL + Qt::Key_A);
        if(bRes)
        {
            pMenu->addAction(pAction);
        }
        pMenu->addSeparator();

        bRes = bRes && makeAction(pAction, pMb, "Print(&P)", Qt::CTRL + Qt::Key_P);
        if(bRes)
        {
            pMenu->addAction(pAction);
        }
        pMenu->addSeparator();

        bRes = bRes && makeAction(pAction, pMb, "Exit(X)", Qt::CTRL + Qt::Key_X);
        if(bRes)
        {
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
    QMenu* pMenu = new QMenu("Edit(&E)");

    bool bRes = true;
    if(NULL != pMenu)
    {
        QAction* pAction = NULL;

        bRes = bRes && makeAction(pAction, pMb, "Undo(&U)", Qt::CTRL + Qt::Key_U);
        if(bRes)
        {
            pMenu->addAction(pAction);
        }
        pMenu->addSeparator();

        bRes = bRes && makeAction(pAction, pMb, "Redo(&R)", Qt::CTRL + Qt::Key_R);
        if(bRes)
        {
            pMenu->addAction(pAction);
        }
        pMenu->addSeparator();

        bRes = bRes && makeAction(pAction, pMb, "Cut(&T)", Qt::CTRL + Qt::Key_T);
        if(bRes)
        {
            pMenu->addAction(pAction);
        }
        pMenu->addSeparator();

        bRes = bRes && makeAction(pAction, pMb, "Copy(&C)", Qt::CTRL + Qt::Key_C);
        if(bRes)
        {
            pMenu->addAction(pAction);
        }
        pMenu->addSeparator();

        bRes = bRes && makeAction(pAction, pMb, "Paste(&P)", Qt::CTRL + Qt::Key_P);
        if(bRes)
        {
            pMenu->addAction(pAction);
        }
        pMenu->addSeparator();

        bRes = bRes && makeAction(pAction, pMb, "Delete(&D)", Qt::CTRL + Qt::Key_D);
        if(bRes)
        {
            pMenu->addAction(pAction);
        }
        pMenu->addSeparator();

        bRes = bRes && makeAction(pAction, pMb, "Find(&F)", Qt::CTRL + Qt::Key_F);
        if(bRes)
        {
            pMenu->addAction(pAction);
        }
        pMenu->addSeparator();

        bRes = bRes && makeAction(pAction, pMb, "Replace(&R)...", Qt::CTRL + Qt::Key_R);
        if(bRes)
        {
            pMenu->addAction(pAction);
        }
        pMenu->addSeparator();

        bRes  = bRes && makeAction(pAction, pMb, "Goto(&G)...", Qt::CTRL + Qt::Key_G);
        if(bRes)
        {
            pMenu->addAction(pAction);
        }
        pMenu->addSeparator();

        bRes = bRes && makeAction(pAction, pMb, "Select All(&A)", Qt::CTRL + Qt::Key_A);
        if(bRes)
        {
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
    QMenu* pMenu = new QMenu("Format(&F)");

    bool bRes = true;
    if(NULL != pMenu)
    {
        QAction* pAction = NULL;

        bRes = bRes && makeAction(pAction, pMb, "Auto Wrap(&W)", Qt::CTRL + Qt::Key_W);
        if(bRes)
        {
            pMenu->addAction(pAction);
        }
        pMenu->addSeparator();

        bRes = bRes && makeAction(pAction, pMb, "Font(&F)...", Qt::CTRL + Qt::Key_F);
        if(bRes)
        {
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
    QMenu* pMenu = new QMenu("View(&V)");

    bool bRes = true;
    if(NULL != pMenu)
    {
        QAction* pAction = NULL;

        bRes = bRes && makeAction(pAction, pMb, "Tool Bar(&T)", Qt::CTRL + Qt::Key_O);
        if(bRes)
        {
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
    QMenu* pMenu = new QMenu("Help(&H)");

    bool bRes = true;
    if(NULL != pMenu)
    {
        QAction* pAction = NULL;

        bRes = bRes && makeAction(pAction, pMb, "User Manual(&U)", Qt::CTRL + Qt::Key_U);
        if(bRes)
        {
            pMenu->addAction(pAction);
        }
        pMenu->addSeparator();

        bRes = bRes && makeAction(pAction, pMb, "About NotePad...", 0);
        if(bRes)
        {
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
    }

    bRes = bRes && makeAction(pAction, pTb, "Open", ":/Res/pic/open.png");
    if(bRes)
    {
        pTb->addAction(pAction);
    }

    bRes = bRes && makeAction(pAction, pTb, "Save", ":/Res/pic/save.png");
    if(bRes)
    {
        pTb->addAction(pAction);
    }

    bRes = bRes && makeAction(pAction, pTb, "Save As", ":/Res/pic/saveas.png");
    if(bRes)
    {
        pTb->addAction(pAction);
    }

    bRes = bRes && makeAction(pAction, pTb, "Print", ":/Res/pic/print.png");
    if(bRes)
    {
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
        pTb->addAction(pAction);
    }

    bRes = bRes && makeAction(pAction, pTb, "Redo", ":/Res/pic/redo.png");
    if(bRes)
    {
        pTb->addAction(pAction);
    }

    bRes = bRes && makeAction(pAction, pTb, "Cut", ":/Res/pic/cut.png");
    if(bRes)
    {
        pTb->addAction(pAction);
    }

    bRes = bRes && makeAction(pAction, pTb, "Copy", ":/Res/pic/copy.png");
    if(bRes)
    {
        pTb->addAction(pAction);
    }

    bRes = bRes && makeAction(pAction, pTb, "Paste", ":/Res/pic/paste.png");
    if(bRes)
    {
        pTb->addAction(pAction);
    }

    bRes = bRes && makeAction(pAction, pTb, "Find", ":/Res/pic/find.png");
    if(bRes)
    {
        pTb->addAction(pAction);
    }

    bRes = bRes && makeAction(pAction, pTb, "Replace", ":/Res/pic/replace.png");
    if(bRes)
    {
        pTb->addAction(pAction);
    }

    bRes = bRes && makeAction(pAction, pTb, "Goto", ":/Res/pic/goto.png");
    if(bRes)
    {
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
        pTb->addAction(pAction);
    }

    bRes = bRes && makeAction(pAction, pTb, "Font", ":/Res/pic/font.png");
    if(bRes)
    {
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
        pTb->addAction(pAction);
    }

    bRes = bRes && makeAction(pAction, pTb, "Status Bar", ":/Res/pic/status.png");
    if(bRes)
    {
        pTb->addAction(pAction);
    }


    return bRes;
}

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

bool MainWindow::makeAction(QAction *&pAction, QWidget* pParent, QString strTip, QString strIconPath)
{
    bool bRes = true;

    pAction = new QAction("",pParent);

    if(NULL != pAction)
    {
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
