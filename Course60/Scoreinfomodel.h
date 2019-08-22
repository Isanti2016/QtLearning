#ifndef _SCOREINFOMODEL_H
#define _SCOREINFOMODEL_H

#include <QObject>
#include <QStandardItemModel>
#include <qList>
#include <QTableView>
#include "ScoreInfo.h"

class ScoreInfoModel : public QObject
{
    Q_OBJECT
public:
    explicit ScoreInfoModel(QObject *parent = nullptr);
    bool Add( QList<ScoreInfo> list);
    bool Add(const ScoreInfo& info);
    bool Remove(int i);
    void Clear();
    ScoreInfo GetItem(int i);
    void SetView(QTableView& view);
    int count();

private:
    QStandardItemModel m_ItemModel;
};

#endif // _SCOREINFOMODEL_H
