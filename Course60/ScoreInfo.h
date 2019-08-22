#ifndef SCOREINFO_H
#define SCOREINFO_H

#include <QObject>

class ScoreInfo : public QObject
{
    Q_OBJECT
public:
    explicit ScoreInfo(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SCOREINFO_H