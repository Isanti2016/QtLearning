#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* pMainWindow = MainWindow::NewInstance();
    pMainWindow->setMinimumSize(600, 400);
    if(NULL != pMainWindow)
    {
        pMainWindow->show();
    }
    return a.exec();
}
