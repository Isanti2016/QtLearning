#include "FindDialog.h"
#include <QEvent>
#include <QString>
#include <QMessageBox>

FindDialog::FindDialog(QWidget* parent, QPlainTextEdit* pText) : QDialog(parent, Qt::WindowCloseButtonHint | Qt::Drawer)
{
    SetPlainTextEdit(pText);
    InitControl();
    ConnectSlot();

}

void FindDialog::SetPlainTextEdit(QPlainTextEdit* pText)
{
    m_pText = pText;
}

QPlainTextEdit* FindDialog::GetPlainTextEdit()
{
    return m_pText;
}

void FindDialog::InitControl()
{
    m_findLbl.setText("Find What:");
    m_findBtn.setText("Find Next");
    m_closeBtn.setText("Close");
    m_matchCheckBox.setText("Match Case");;
    m_backwardBtn.setText("Backward");
    m_forwardBtn.setText("Forward");
    m_forwardBtn.setChecked(true);
    m_radioGrpBx.setTitle("Direction");

    m_hbLayout.addWidget(&m_forwardBtn);
    m_hbLayout.addWidget(&m_backwardBtn);

    m_radioGrpBx.setLayout(&m_hbLayout);

    m_layout.setSpacing(10);
    m_layout.addWidget(&m_findLbl, 0, 0);
    m_layout.addWidget(&m_findEdit, 0, 1);
    m_layout.addWidget(&m_findBtn, 0, 2);
    m_layout.addWidget(&m_matchCheckBox, 1, 0);
    m_layout.addWidget(&m_radioGrpBx, 1, 1);
    m_layout.addWidget(&m_closeBtn, 1, 2);

    setLayout(&m_layout);

    setWindowTitle("Find");
}

bool FindDialog::event(QEvent* evt)
{
    if(evt->type() == QEvent::Close )
    {
        hide();
        return true;
    }

    return QDialog::event(evt);
}

void FindDialog::ConnectSlot()
{
    connect( &m_findBtn, SIGNAL(clicked()), this, SLOT(OnFindClick()) );
    connect( &m_closeBtn, SIGNAL(clicked()), this, SLOT(OnCloseClick()) );
}

void FindDialog::OnFindClick()
{
    QString strTarget = m_findEdit.text();

    if(m_pText != NULL && !strTarget.isEmpty())
    {
        QString strText = m_pText->toPlainText();
        QTextCursor csText = m_pText->textCursor();

        int index = -1;
        Qt::CaseSensitivity CaseSensitive = m_matchCheckBox.isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;

        if( m_forwardBtn.isChecked() )
        {
           index = strText.indexOf(strTarget, csText.position(), CaseSensitive);
           if(index >= 0)
           {
               csText.setPosition(index);
               csText.setPosition(index + strTarget.length(), QTextCursor::KeepAnchor);

               m_pText->setTextCursor(csText);
           }
        }

        if( m_backwardBtn.isChecked() )
        {
            index = strText.lastIndexOf( strTarget, csText.position() - strText.length() - 1, CaseSensitive );
            if(index >= 0)
            {
                csText.setPosition(index + strTarget.length());
                csText.setPosition(index, QTextCursor::KeepAnchor);

                m_pText->setTextCursor(csText);
            }
        }

        if(index < 0)
        {
           QMessageBox msg(this);

           msg.setWindowTitle("Find");
           msg.setText("Can not find \"" + strTarget + "\" any more...");
           msg.setIcon(QMessageBox::Information);
           msg.setStandardButtons(QMessageBox::Ok);

           msg.exec();
        }
    }
}

void FindDialog::OnCloseClick()
{
    close();
}
