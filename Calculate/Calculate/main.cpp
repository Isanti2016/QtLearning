#include <QApplication>
#include <QDebug>
#include "QCalculator.h"




int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

   QCalculator* pCal = QCalculator::NewIntance();
   int ret = -1;

   if(pCal != NULL)
   {
       pCal->show();

       ret = app.exec();

       delete pCal;
   }

    return ret;

}
