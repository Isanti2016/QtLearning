#include <QApplication>
#include "QcalculatoruUI.h"




int main(int argc, char *argv[])
{
    QApplication App(argc, argv);
    int res = -1;
    QCalculatorUI* pQui = QCalculatorUI::NewInstance();
    if( NULL !=  pQui)
    {
        pQui->show();
        res = App.exec();
        delete pQui;
    }

    return res;
}
