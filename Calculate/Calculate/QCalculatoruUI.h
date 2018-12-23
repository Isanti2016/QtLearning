#ifndef _QCALCULATORUI_H_
#define _QCALCULATORUI_H_

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include "Interface.h"

class QCalculatorUI : public QWidget
{
    Q_OBJECT
public:

    ~QCalculatorUI();
    static QCalculatorUI* NewInstance();
    void Show();
    void SetCalculator(CInterface* pInterface);
    CInterface* GetCalculator();
private:
    QLineEdit*      m_edit;
    QPushButton*    m_button[20];
    CInterface*     m_Calculator;

    QCalculatorUI();
    bool Construct();
private slots:
    void OnClickButtonDown();
};

#endif


