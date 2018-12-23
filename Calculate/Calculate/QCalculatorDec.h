#ifndef _QCALCULATORDEC_H_
#define _QCALCULATORDEC_H_

#include <QString>
#include <QQueue>
#include <QStack>
#include "Interface.h"

class QCalculatorDec : public CInterface
{
public:
    QCalculatorDec();
    ~QCalculatorDec();
    bool Expression(QString str);
    QString GetResult();
private:
    QString m_strResult;
    QString Calculator(const QQueue<QString>& strInput);
    QString Operator(const QString& strL, const QString& op, const QString& strr);
    bool Transform(const QQueue<QString>& qEqu, QQueue<QString>& qRes );
    void Split(const QString& strEqu, QQueue<QString>& queEqu);
    bool IsDigitOrDot(const QChar& ch);
    bool IsSymbol(const QString& str);
    bool IsOperator(const QString& ch);
    bool IsSign(const QChar& ch);
    bool IsLeftBracket(const QString& ch);
    bool IsRightBracket(const QString& ch);
    int  Priority(const QString& str);
    bool IsLegal(const QQueue< QString>& strEqu);
    bool IsNumber(QString str);
};

#endif // QCALCULATORDEC_H
