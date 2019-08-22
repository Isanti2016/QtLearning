#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QObject>
#include <QList>
#include "ScoreInfo.h"

class DataSource : public QObject
{
    Q_OBJECT
public:
    explicit DataSource(QObject *parent = nullptr);

    bool SetPath(QString strPath);
    int count();
    QList<ScoreInfo> fetchData();

private:
    QList<ScoreInfo> m_data;

    bool Parase(QString strLine, ScoreInfo& Info);

};

#endif // DATASOURCE_H
