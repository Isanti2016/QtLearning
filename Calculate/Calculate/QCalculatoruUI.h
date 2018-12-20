#ifndef _QCALCULATORUI_H_
#define _QCALCULATORUI_H_

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class QCalculatorUI : public QWidget
{
    Q_OBJECT
public:
    static QCalculatorUI* NewInstance();
    ~QCalculatorUI();
private:
    void Show();
    bool Construct();
    QCalculatorUI();
    QLineEdit* m_edit;
    QPushButton* m_button[20];

private slots:
    void OnClickButtonDown();
};

#endif


