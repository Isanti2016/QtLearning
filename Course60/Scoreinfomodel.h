#ifndef SCOREINFOMODEL_H
#define SCOREINFOMODEL_H

#include <QObject>

class ScoreInfoModel : public QObject
{
    Q_OBJECT
public:
    explicit ScoreInfoModel(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SCOREINFOMODEL_H