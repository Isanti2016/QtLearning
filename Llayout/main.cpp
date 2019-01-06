#include "LayoutTest.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CLayoutTest objLayout;
    objLayout.show();

    return a.exec();
}
