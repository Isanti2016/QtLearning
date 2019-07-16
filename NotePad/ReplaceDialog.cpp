#include "ReplaceDialog.h"


ReplaceDialog::ReplaceDialog(QWidget *parent, QPlainTextEdit* pText)
              : FindDialog(parent, pText)
{
    InitControl();
    ConnectSlot();

    setWindowTitle("Replace");
}


void ReplaceDialog::InitControl()
{
    m_replaceLbl.setText("Replace To:");
    m_replaceBtn.setText("Replace");
    m_replaceAllBtn.setText("Replace ALL");

    m_layout.removeWidget(&m_matchCheckBox);
    m_layout.removeWidget(&m_radioGrpBx);;
    m_layout.removeWidget(&m_closeBtn);

    m_layout.addWidget(&m_replaceLbl, 1, 0);
    m_layout.addWidget(&m_replaceEdit, 1, 1);
    m_layout.addWidget(&m_replaceBtn, 1, 2);
    m_layout.addWidget(&m_matchCheckBox, 2, 0);
    m_layout.addWidget(&m_radioGrpBx, 2, 1);
    m_layout.addWidget(&m_replaceAllBtn, 2, 2);

    m_layout.addWidget(&m_closeBtn, 3, 2);
}

void ReplaceDialog::ConnectSlot()
{
    connect(&m_replaceBtn, SIGNAL(clicked()), this, SLOT(onReplaceClicked()));
    connect(&m_replaceAllBtn, SIGNAL(clicked()), this, SLOT(OnReplaceAllClicked()));
}

void ReplaceDialog::onReplaceClicked()
{
    QString strFrom = m_findEdit.text();
    QString strTo   = m_replaceEdit.text();

    if( (m_pText != NULL) && (strFrom != "") )
    {
        QString strSelect = m_pText->textCursor().selectedText();

        if(strSelect == strFrom)
        {
            m_pText->insertPlainText(strTo);
        }

        OnFindClick();
    }
}

void ReplaceDialog::OnReplaceAllClicked()
{
    QString strFrom = m_findEdit.text();
    QString strTo   = m_replaceEdit.text();
    if( (m_pText != NULL ) && (strFrom != "") )
    {
        QString strText = m_pText->toPlainText();
        strText.replace( strFrom, strTo, m_matchCheckBox.isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive );

        m_pText->clear();
        m_pText->insertPlainText(strText);

    }
}
