#include "Scoreinfomodel.h"
#include <QStandardItem>
#include <QStringList>

ScoreInfoModel::ScoreInfoModel(QObject *parent) : QObject(parent)
{

}

bool ScoreInfoModel::Add( QList<ScoreInfo> list)
{
    bool bRes = true;
    for( int i=0; i< list.count() && bRes; ++i)
    {
        bRes = Add( list.at(i) );
    }

    return bRes;
}

bool ScoreInfoModel::Add(const ScoreInfo &info)
{
    bool bRes = true;

    //设置标题
    if( count() == 0 )
    {
        QStringList list;
        list.append("ID");
        list.append("Name");
        list.append("Score");

        m_ItemModel.setHorizontalHeaderLabels(list);

    }

    QStandardItem* root = m_ItemModel.invisibleRootItem();
    QStandardItem* item0 = new QStandardItem;
    QStandardItem* item1 = new QStandardItem;
    QStandardItem* item2 = new QStandardItem;

    if( (root != NULL) && (item0 != NULL) && (item1 != NULL) && (item2 != NULL) )
    {
        item0->setData( info.Id(), Qt::DisplayRole);
        item1->setData( info.Name(), Qt::DisplayRole );
        item2->setData( info.Score(), Qt::DisplayRole );

        item0->setEditable(false);
        item1->setEditable(false);
        item2->setEditable(false);

        int iRow = count();
        root->setChild(iRow, 0, item0);
        root->setChild(iRow, 1, item1);
        root->setChild(iRow, 2, item2);
    }
    else
    {
        bRes = false;
    }

    return bRes;
}

bool ScoreInfoModel::Remove(int i)
{
    bool bRes = true;

    if( (i >=0) && (i <= count()))
    {
        m_ItemModel.removeRow(i);
    }
    else
    {
        bRes = false;
    }

    return bRes;
}

void ScoreInfoModel::Clear()
{
    m_ItemModel.clear();
}

ScoreInfo ScoreInfoModel::GetItem(int i)
{
    ScoreInfo ret;
    if( (0 <= i) && (i<count()) )
    {
        QModelIndex index0 = m_ItemModel.index( i, 0, QModelIndex() );
        QModelIndex index1 = m_ItemModel.index( i, 1, QModelIndex() );
        QModelIndex index2 = m_ItemModel.index( i, 2, QModelIndex() );

        QVariant v0 = index0.data( Qt::DisplayRole );
        QVariant v1 = index1.data( Qt::DisplayRole );
        QVariant v2 = index2.data( Qt::DisplayRole );

        ret = ScoreInfo( v0.toString(), v1.toString(), v2.toInt() );
    }

    return ret;
}

void ScoreInfoModel::SetView(QTableView &view)
{
    //设置到视图
    view.setModel( &m_ItemModel );
}

int ScoreInfoModel::count()
{
    return m_ItemModel.rowCount();
}
