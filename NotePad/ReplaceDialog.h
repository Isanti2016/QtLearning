#ifndef REPLACEDIALOG_H
#define REPLACEDIALOG_H

#include "FindDialog.h"

#include <QObject>
#include <QWidget>

class ReplaceDialog : public FindDialog
{
    Q_OBJECT

protected:
    QLabel m_replaceLbl;
    QLineEdit m_replaceEdit;
    QPushButton m_replaceBtn;
    QPushButton m_replaceAllBtn;

    void InitControl();
    void ConnectSlot();

protected slots:
    void onReplaceClicked();
    void OnReplaceAllClicked();

public:
    explicit ReplaceDialog(QWidget *parent = nullptr, QPlainTextEdit* pText = nullptr);

signals:

public slots:
};

#endif // REPLACEDIALOG_H
