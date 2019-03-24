#ifndef FINDDIALOG_H
#define FINDDIALOG_H
#include <QDialog>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QRadioButton>
#include <QGroupBox>
#include <QPointer>
#include <QPlainTextEdit>


class FindDialog : public QDialog
{
    Q_OBJECT

protected slots:
    void OnFindClick();
    void OnCloseClick();

protected:

    QGroupBox m_radioGrpBx;

    QHBoxLayout m_hbLayout;
    QGridLayout m_layout;

    QLabel m_findLbl;
    QLineEdit m_findEdit;
    QPushButton m_findBtn;
    QPushButton m_closeBtn;
    QCheckBox m_matchCheckBox;
    QRadioButton m_forwardBtn;
    QRadioButton m_backwardBtn;

    QPointer<QPlainTextEdit> m_pText;

public:
    explicit FindDialog(QWidget* parent = 0, QPlainTextEdit* m_Text = 0);
    void SetPlainTextEdit(QPlainTextEdit* pText);
    QPlainTextEdit* GetPlainTextEdit();

    void InitControl();
    bool event(QEvent* evt);

    void ConnectSlot();
};

#endif // FINDDIALOG_H
