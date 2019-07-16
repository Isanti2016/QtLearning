#include <QCoreApplication>
#include <math.h>
#include <iostream>

using namespace std;
const double PRECISION = 0.000001;

//获得余数
double GetReminder(double dDividend, double dDivisor )
{
    //却绝对值
    double dNum1 = fabs(dDividend);
    double dNum2 = fabs(dDivisor);

    // 获得商，进行四舍五入
    int iQuotient = (int)(dNum1 / dNum2 + 0.5);
    //获得 商 * 除数
    double dValue = iQuotient * dNum2;
    //获得余数
    double dRes = fabs(dNum1 - dValue);

    return dRes;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    while(true)
    {
        double dNum1, dNum2;
        cin >> dNum1 >> dNum2;

        double dReminder = GetReminder(dNum1, dNum2);
        cout << "Reminder: " << dReminder <<endl;
        if( dReminder < PRECISION )
        {
            cout << "Multiple: True"<<endl;
        }
        else
        {
            cout << "Multiple: False"<<endl;
        }
    }

    return a.exec();
}
