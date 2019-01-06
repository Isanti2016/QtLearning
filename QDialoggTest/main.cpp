#include <QApplication>
#include "WidgetTest.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WidgetTest w;
    w.show();

    return a.exec();
}
