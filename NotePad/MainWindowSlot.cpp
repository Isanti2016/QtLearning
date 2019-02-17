#include "MainWindow.h"
#include <QString>
#include <QDebug>
#include <QStringList>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>


QString MainWindow::showFileDialog(QFileDialog::AcceptMode OpenMode,  QString strTitle)
{
    QString strPath;
    QFileDialog fd(this);

    QStringList filters;
    filters.append("Text Files (*.txt)");
    filters.append("All Files (*)");

    //设置标题
    fd.setWindowTitle(strTitle);
    //设置打开、存储模式
    fd.setAcceptMode(OpenMode);
    //设置文件滤波
    fd.setNameFilters(filters);

    if( OpenMode ==  QFileDialog::AcceptOpen )
    {
        //打开模式下，仅选择单个文件
        fd.setFileMode( QFileDialog::ExistingFile );
    }

    if(fd.exec() == QFileDialog::Accepted)
    {
        //返回选择的文件
        strPath = fd.selectedFiles()[0];
    }
    return strPath;
}

void MainWindow::showErrorMessage(QString strMessage)
{
    QMessageBox dlgMsg(this);

    dlgMsg.setWindowTitle("Error");
    dlgMsg.setText(strMessage);
    dlgMsg.setIcon(QMessageBox::Critical);
    dlgMsg.setStandardButtons(QMessageBox::Ok);

    dlgMsg.exec();
}

void MainWindow::OnFileOpen()
{
    QString strPath = showFileDialog(QFileDialog::AcceptOpen, "Open Files");

    if(strPath != "")
    {
        //打开文件
        QFile file(strPath);
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QByteArray byteText = file.readAll();
            QString strText(byteText);

            //文件内容显示到文本编辑框中
            m_objMainEditor.setPlainText(strText);
            file.close();

            m_strPath = strPath;
            setWindowTitle("NotePad - [ " + m_strPath + " ]");
        }
        else
        {
            showErrorMessage("Open file error! \n" + strPath);
        }
    }

}

void MainWindow::OnFileSave()
{
    //没有存储地址时，要先获取地址
    if(m_strPath == "")
    {
        m_strPath = showFileDialog(QFileDialog::AcceptSave, "Save");
    }

    //打开文件，进行写入
    QFile file(m_strPath);
    if(file.open( QIODevice::WriteOnly | QIODevice::Text ))
    {
        //因为 file.write(const char *data)需要转为char*
        QTextStream outText(&file);

        //文本编辑框内容写入到文件中
        outText << m_objMainEditor.toPlainText();

        file.close();
        setWindowTitle("NotePad - [ " + m_strPath + " ]");
    }
    else
    {
        showErrorMessage("Open file error! \n" + m_strPath);
        m_strPath = "";
    }

}

void MainWindow::OnFileSavaAs()
{
     QString strPath = showFileDialog(QFileDialog::AcceptSave, "Save As");

     if(strPath != "")
     {
         QFile file(strPath);

         //打开文件
         if(file.open( QIODevice::WriteOnly | QIODevice::Text ))
         {
             QTextStream outText(&file);

             //文本编辑框内容写入到文件中
             outText << m_objMainEditor.toPlainText();
             file.close();

             m_strPath = strPath;
             setWindowTitle("NotePad - [ " + m_strPath + " ]");
         }
         else
         {
             showErrorMessage("Open file error! \n" + strPath);
         }

     }
}
