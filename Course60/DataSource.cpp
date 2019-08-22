#include "DataSource.h"
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QStringList>

DataSource::DataSource(QObject *parent) : QObject(parent)
{

}

bool DataSource::SetPath(QString strPath)
{
    bool bRes = true;
    QFile file(strPath);
    if( file.open( QIODevice::ReadOnly ) )
    {
        QTextStream objTs(&file);
        //处理QFile读中文乱码的问题
        objTs.setCodec("UTF-8");

        while( !objTs.atEnd() && bRes)
        {
            ScoreInfo info;
            if( Parase( objTs.readLine(), info ) )
            {
                m_data.append( info );
            }
            else
            {
                bRes = false;
            }
        }
    }
    else
    {
        bRes = false;
    }

    return bRes;
}

bool DataSource::Parase(QString strLine, ScoreInfo &Info)
{
    bool bRes = true;
    QStringList list = strLine.split("，", QString::SkipEmptyParts );
    if( list.count() == 3 )
    {
        QString strId = list[0].trimmed();
        QString strName = list[1].trimmed();
        QString strScore = list[2].trimmed();
        int ivalue = strScore.toInt();
        if( ivalue >=0 && ivalue <= 150 )
        {
            Info = ScoreInfo(strId, strName, strScore.toInt());
        }

    }
    else
    {
        bRes = false;
    }

    return bRes;
}

int DataSource::count()
{
    return m_data.count();
}

QList<ScoreInfo> DataSource::fetchData()
{
    QList<ScoreInfo> obj = m_data;

    m_data.clear();
    return obj;
}
