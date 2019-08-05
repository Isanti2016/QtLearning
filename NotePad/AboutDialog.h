#ifndef _ABOUTDIALOG_H
#define _ABOUTDIALOG_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QPlainTextEdit>
#include <QPushButton>

class CAboutDialog : public QDialog
{

    QLabel          m_logolbl;
    QPlainTextEdit  m_infoEidt;
    QPushButton     m_closeBtn;
    QLabel          m_Contact_Info;

public:
    CAboutDialog(/*QWidget *parent*/);
};

#endif // _ABOUTDIALOG_H
