#ifndef WIDGETT_H
#define WIDGETT_H

#include <QWidget>
#include <QFileSystemModel>
#include <QPlainTextEdit>
#include <QString>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    QFileSystemModel m_objFSM;
    QPlainTextEdit m_objEdit;

private slots:
    void DirectoryLoad(QString strPath);
};

#endif // WIDGETT_H
