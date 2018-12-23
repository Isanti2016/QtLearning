#include <QDebug>
#include <math.h>
#include "QCalculatorDec.h"


QCalculatorDec::QCalculatorDec()
{

}

QCalculatorDec::~QCalculatorDec()
{

}

QString QCalculatorDec::GetResult()
{
    return m_strResult;
}

bool QCalculatorDec::Expression(QString str)
{
    bool bRes = false;
    QString strRes = "error";
    QQueue< QString > queSplit;
    QQueue< QString > queTransfom;
    Split(str, queSplit);
    if( Transform(queSplit, queTransfom))
    {
        strRes = Calculator(queTransfom);
    }
    else
    {
        strRes = "error";
    }
    bRes = (strRes != "Error");
    if(bRes)
    {
        m_strResult = strRes;
    }
    return bRes;
}

QString QCalculatorDec::Calculator(const QQueue<QString> &strInput)
{
    QQueue<QString> Input = strInput;
    QString strRes = "error";
    QStack<QString> stack;
    while( !Input.isEmpty() )
    {
        QString str = Input.dequeue();
        if(!IsSymbol(str) )
        {
            stack.push(str);
        }
        else if(IsOperator(str))
        {
            if( stack.size() >= 2 )
            {
                QString strR = stack.pop();
                QString strL = stack.pop();
                strRes = Operator(strL, str, strR);
                stack.append(strRes);
            }
        }
        else
        {
            strRes = "error";
            break;
        }
    }
    if(stack.length() == 1 && strRes != "error")
    {
        return stack.pop();
    }
    else
    {
        return "error";
    }
}

QString QCalculatorDec::Operator(const QString &strL, const QString &op, const QString &strR)
{
    QString strRes = "";
    double dRes;
    if( IsNumber(strL) && IsNumber(strR) )
    {
        double dL = strL.toDouble();
        double dr = strR.toDouble();
        if( op == "+" )
        {
            dRes = dL + dr;
        }
        else if( op == "-")
        {
            dRes = dL - dr;
        }
        else if( op == "*")
        {
            dRes = dL * dr;
        }
        else if( op == "/")
        {
            const double EPSILON = 0.0000001;
            if(fabs(dr) > EPSILON)
            {
                dRes = dL / dr;
            }
            else
            {
                strRes = "error";
            }
        }
        else
        {
            strRes = "error";
        }
    }

    if(strRes != "error")
    {
        strRes = QString::number(dRes,'f');
    }
    return strRes;
}

bool QCalculatorDec::Transform( const QQueue<QString> &qInput, QQueue<QString> &qOutput )
{
    //判断表达式的合法性
    bool bRes = IsLegal(qInput);

    QStack< QString > sTmp;
    for( unsigned int i = 0; i < qInput.length() && bRes; ++i)
    {
        QString  strTmp = qInput.at(i);

        if ( !IsSymbol(strTmp) )
        {
            qOutput.append( strTmp );
        }
        else if( IsOperator(strTmp) )
        {
            while( !sTmp.isEmpty() && Priority(strTmp) <= Priority(sTmp.top()) )
            {
                qOutput.append( sTmp.pop() );
            }
            sTmp.append( strTmp );
        }
        else if( IsLeftBracket( strTmp) )
        {
            sTmp.append( strTmp );
        }
        else if ( IsRightBracket( strTmp ) )
        {
            while( !sTmp.isEmpty() && !IsLeftBracket(sTmp.top()) )
            {
                qOutput.append( sTmp.pop() );
            }
            if(!sTmp.isEmpty())
            {
                sTmp.pop();
            }
        }
        else
        {
            //不存在的情况
            bRes = false;
        }
    }
    while(!sTmp.isEmpty() )
    {
        qOutput.append( sTmp.pop() );
    }
    if(!bRes)
    {
        qOutput.clear();
    }
    return bRes;
}

void QCalculatorDec::Split(const QString &strEqu, QQueue<QString>& queEqu)
{
    queEqu.clear();
    QString strNumber = "";
    QString strPre = "";

    for( unsigned int i = 0; i < strEqu.length(); ++i)
    {
        QChar chTmp = strEqu.at(i);
        if( IsDigitOrDot(chTmp) )
        {
            strNumber += chTmp;
            strPre  = chTmp;
        }
        else if( IsSymbol(chTmp) )
        {
            if( !strNumber.isEmpty() )
            {
                queEqu.append(strNumber );
                strNumber.clear();
            }

            if( IsSign(chTmp) && (strPre  == "" || strPre  == "(" || IsOperator(strPre )) )
            {
                strNumber += chTmp;
            }
            else
            {
                queEqu.append(chTmp);
            }
            strPre  = chTmp;
        }
    }

    if(!strNumber.isEmpty())
    {
        queEqu.append(strNumber);
    }

}

bool QCalculatorDec::IsDigitOrDot(const QChar& ch)
{
    return ('0' <= ch && '9' >= ch) || ch == '.';
}

bool QCalculatorDec::IsSymbol(const QString& ch)
{
    return IsOperator(ch) || ch == '(' || ch == ')';
}

bool QCalculatorDec::IsOperator(const QString &ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

bool QCalculatorDec::IsSign(const QChar &ch)
{
    return ch == '+' || ch == '-';
}

bool QCalculatorDec::IsLeftBracket(const QString &ch)
{
    return (ch == '(') ? true : false;
}

bool QCalculatorDec::IsRightBracket(const QString &ch)
{
    return (ch == ')') ? true : false;
}

int QCalculatorDec::Priority(const QString &str)
{
    if( str == '+' || str == '-')
        return 1;
    if(str == '*' || str == '/')
        return 2;
}

bool QCalculatorDec::IsLegal(const QQueue< QString>& strEqu)
{
    bool bRes = true;
    QStack<QString> sTmp;
    for(unsigned int i = 0; i < strEqu.length(); ++i)
    {
        QString strTmp = strEqu.at(i);
        if( strTmp == "(" )
        {
            sTmp.push(strTmp);
        }
        else if( strTmp == ")" )
        {
            if( !sTmp.isEmpty() && sTmp.top() == "(" )
            {
                sTmp.pop();
            }
            else
            {
                bRes = false;
                break;
            }
        }
    }
    return bRes;
}

bool QCalculatorDec::IsNumber(QString str)
{
    bool ret = false;

    str.toDouble(&ret);

    return ret;
}
