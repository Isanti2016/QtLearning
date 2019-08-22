#include "Widgett.h"
#include <QDir>
#include <QByteArray>
#include <QBuffer>
#include <QDataStream>
#include <QIODevice>
#include <QModelIndex>
#include <QTextStream>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    m_objEdit.setParent(this);
    m_objEdit.move(10,10);
    m_objEdit.resize(500, 500);

    connect(&m_objFSM, SIGNAL(directoryLoaded(QString)), this, SLOT(DirectoryLoad(QString)) );
    m_objFSM.setRootPath( QDir::currentPath() );
}

Widget::~Widget()
{


}

void Widget::DirectoryLoad(QString strPath)
{
    QModelIndex root = m_objFSM.index(strPath);

    QByteArray objArr;
    QBuffer objBuf(&objArr);

    if( objBuf.open(QIODevice::WriteOnly) )
    {
        QTextStream out(&objBuf);

        out << m_objFSM.isDir(root) << endl;
        out << m_objFSM.data(root).toString() << endl;
        out << m_objFSM.filePath(root) << endl;
        out << m_objFSM.fileName(root) << endl;
        out << &m_objFSM << endl;

        out << root.model() << endl;
        out << root.data().toString() << endl;

        for(int i = 0; i < m_objFSM.rowCount(root); ++i)
        {
            QModelIndex ci = m_objFSM.index(i, 0, root);
            out << ci.data().toString() << endl;
        }

        objBuf.close();
    }

    if( objBuf.open(QIODevice::ReadOnly) )
    {
        QTextStream in(&objBuf);
        m_objEdit.insertPlainText( in.readAll() );
        objBuf.close();
    }

}
