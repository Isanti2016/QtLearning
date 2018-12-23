#ifndef _CINTERFACE_H_
#define _CINTERFACE_H_
#include <QString>

class CInterface
{

public:
    virtual bool Expression(QString str) = 0;
    virtual QString GetResult() = 0;
};

#endif
