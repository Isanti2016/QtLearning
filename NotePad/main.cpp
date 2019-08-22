#include "MainWindow.h"
#include <QApplication>
#include <QFileInfo>

void ApplyCmdPara( int argc, char *argv[], MainWindow* pMainWindow )
{
    if(argc > 1)
    {
        QFileInfo objFileInfo( argv[1] );
        if( objFileInfo.exists() )
        {
            pMainWindow->OnCmdFileOpen( objFileInfo.absoluteFilePath() );
        }
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* pMainWindow = MainWindow::NewInstance();
    int iRet = -1;
    if(NULL != pMainWindow)
    {
        ApplyCmdPara(argc, argv, pMainWindow);

        pMainWindow->show();

        iRet = a.exec();
    }
    delete pMainWindow;
    return iRet;
}
