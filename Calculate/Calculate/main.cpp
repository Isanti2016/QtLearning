#include <QApplication>
#include <QDebug>
#include "QCalculatoruUI.h"
#include "QCalculatorDec.h"




int main(int argc, char *argv[])
{

    //"-9+-10*2+(-4+6)+59";
    QString strEqu = "-9+-10*2+(-4+6)+59";
    QCalculatorDec test;
    qDebug() <<test.Expression(strEqu)<<endl;
    return 0;

}
