#include "MainWindow.h"
#include <QString>
#include <QDebug>
#include <QStringList>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QList>
#include <QUrl>
#include <QFileInfo>
#include <QObjectList>
#include <QAction>
#include <QMenuBar>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QTextCursor>

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

int MainWindow::showQueryMessage(QString strMessage)
{
    QMessageBox dlgMsg(this);

    dlgMsg.setWindowTitle("Query");
    dlgMsg.setText(strMessage);
    dlgMsg.setIcon(QMessageBox::Question);
    dlgMsg.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

    return dlgMsg.exec();
}

QString MainWindow::saveCurrentData(QString strPath)
{
    QString strRes = strPath;
    //没有存储地址时，要先获取地址
    if(strRes == "")
    {
        strRes = showFileDialog(QFileDialog::AcceptSave, "Save");
    }

    if(strRes != "")
    {
        //打开文件，进行写入
        QFile file(strRes);
        if(file.open( QIODevice::WriteOnly | QIODevice::Text ))
        {
            //因为 file.write(const char *data)需要转为char*
            QTextStream outText(&file);

            //文本编辑框内容写入到文件中
            outText << m_objMainEditor.toPlainText();

            file.close();
            setWindowTitle("NotePad - [ " + strRes + " ]");

            m_isTextChanged = false;
        }
        else
        {
            showErrorMessage("Open file error! \n" + strRes);
            strRes = "";
        }
    }
    return strRes;
}

void MainWindow::preEditChange()
{
    if(m_isTextChanged)
    {
        int iRes = showQueryMessage("Do you want to save the changes file?");

        switch (iRes) {
        case QMessageBox::Yes:
            saveCurrentData(m_strPath);
            break;
        case QMessageBox::No:
            m_isTextChanged = false;
            break;
        case QMessageBox::Cancel:
            break;
        default:
            break;
        }
    }
}

void MainWindow::openFileToEditor(QString strPath)
{
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
            m_isTextChanged = false;
        }
        else
        {
            showErrorMessage("Open file error! \n" + strPath);
        }
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    preEditChange();

    if(!m_isTextChanged)
    {
        MainWindow::closeEvent(event);
    }
    else
    {
        event->ignore();
    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent* e)
{
    if( e->mimeData()->hasUrls() )
    {
        e->acceptProposedAction();
    }
    else
    {
        e->ignore();
    }
}

void MainWindow::dropEvent(QDropEvent* e)
{
    if(e->mimeData()->hasUrls())
    {
        QList<QUrl> list = e->mimeData()->urls();
        QString path = list[0].toLocalFile();
        QFileInfo info(path);

        if(info.isFile())
        {
            preEditChange();
            if(!m_isTextChanged)
            {
                openFileToEditor(path);
            }
        }
        else
        {
            showErrorMessage("Cannot open a folder!");
        }
    }
    else
    {
        e->ignore();
    }
}

void MainWindow::OnFileOpen()
{
    //处理文件改变
    preEditChange();

    if(!m_isTextChanged)
    {
        QString strPath = showFileDialog(QFileDialog::AcceptOpen, "Open Files");
        openFileToEditor(strPath);
    }
}

void MainWindow::OnFileSave()
{
    QString strPath = saveCurrentData(m_strPath);

    if(strPath != "")
    {
        m_strPath = strPath;
    }

}

void MainWindow::OnFileSavaAs()
{
     QString strPath;
     strPath = saveCurrentData();
     if(strPath != "")
     {
         m_strPath = strPath;
     }

}

void MainWindow::OnFileNew()
{
    //处理文件改变
    preEditChange();

    if(!m_isTextChanged)
    {
        m_objMainEditor.clear();

        setWindowTitle("NotePad - [ New ]");

        m_strPath = "";

        m_isTextChanged = false;
    }


}

void MainWindow::OnTextChanged()
{
    if(!m_isTextChanged)
    {
        setWindowTitle( "*" + windowTitle());
    }

    m_isTextChanged = true;
}

//在菜单中根据字符串找到动作
QAction* MainWindow::findMenuBarAction(QString strAction)
{
    QAction* pAction = NULL;

    const QObjectList& menuList =  menuBar()->children();        //menuBar中保护menu的列表
    for(int i = 0 ;i < menuList.count(); ++i)
    {
        QMenu* objMenu = dynamic_cast<QMenu*>(menuList.at(i));
        if(NULL != objMenu)
        {
            const QList<QAction*>& actList = objMenu->actions(); //menu中保护Action的列表
            for(int j = 0; j < actList.count(); ++j)
            {
                if( actList[j]->text().startsWith(strAction, Qt::CaseInsensitive) )
                {
                    pAction = actList[j];
                    break;
                }
            }
        }
    }

    return pAction;
}

//在工具栏中根据字符串找到动作
QAction* MainWindow::findToolBarAction(QString strAction)
{
    QAction* pAction = NULL;

    const QObjectList& toolList = children();
    for(int i = 0; i < toolList.count(); ++i)
    {
        QToolBar* pToolBar = dynamic_cast<QToolBar*>(toolList.at(i));
        if(NULL != pToolBar)
        {
            QList<QAction*> actList = pToolBar->actions();

            for(int j = 0; j < actList.count(); ++j)
            {
                if( actList[j]->toolTip().startsWith(strAction, Qt::CaseInsensitive) )
                {
                    pAction = actList[j];
                    break;
                }
            }
        }
    }

    return pAction;
}

//根据QPlainTextEdit提供的信号，设置对应的按钮状态
void MainWindow::OnCopyAvailable(bool bAvailable)
{
    QAction* pAction = NULL;
    pAction = findMenuBarAction("copy");
    if ( NULL != pAction )
    {
        pAction->setEnabled(bAvailable);
    }

    pAction = findToolBarAction("Copy");
    if ( NULL != pAction )
    {
        pAction->setEnabled(bAvailable);
    }

    pAction = findMenuBarAction("cut");
    if ( NULL != pAction )
    {
        pAction->setEnabled(bAvailable);
    }

    pAction = findToolBarAction("cut");
    if ( NULL != pAction )
    {
        pAction->setEnabled(bAvailable);
    }

}

void MainWindow::OnUndoAvailable(bool bAvailable)
{
    QAction* pAction = NULL;
    pAction = findMenuBarAction("Undo");
    if ( NULL != pAction )
    {
        pAction->setEnabled(bAvailable);
    }

    pAction = findToolBarAction("Undo");
    if ( NULL != pAction )
    {
        pAction->setEnabled(bAvailable);
    }

}

void MainWindow::OnRedoAvailable(bool bAvailable)
{
    QAction* pAction = NULL;
    pAction = findMenuBarAction("redo");
    if ( NULL != pAction )
    {
        pAction->setEnabled(bAvailable);
    }

    pAction = findToolBarAction("redo");
    if ( NULL != pAction )
    {
        pAction->setEnabled(bAvailable);
    }
}

//处理打印功能
void MainWindow::OnFilePrinter()
{
    QPrintDialog objPrint(this);

    objPrint.setWindowTitle("Print");

    if(objPrint.exec() == QDialog::Accepted)
    {
        QPrinter* pt = objPrint.printer();

        QTextDocument* pText = m_objMainEditor.document();

        pText->print(pt);
    }
}

//显示光标位置
void MainWindow::OnCursorPositionChange()
{
    unsigned int uPos = m_objMainEditor.textCursor().position();
    QString strText = m_objMainEditor.toPlainText();

    unsigned int Row = 0;
    unsigned int Col = 0;
    unsigned int flag = 0;

    for(unsigned int i = 0; i < uPos; ++i)
    {
        if( strText[i] == "\n" )
        {
            ++Row;
            flag = i;       //存储字数
        }
    }

    Col = uPos - flag - 1;

    m_objStatusLabel.setText("Ln: " + QString::number(Row + 1) +"    Col: " + QString::number(Col + 1));

}
