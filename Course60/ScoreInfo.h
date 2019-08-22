#ifndef SCOREINFO_H
#define SCOREINFO_H

#include <QObject>
#include <QString>

class ScoreInfo : public QObject
{
    Q_OBJECT
public:
    explicit ScoreInfo(QObject *parent = nullptr);
    explicit ScoreInfo(QString id, QString name, int score, QObject *parent = nullptr);

    ScoreInfo(const ScoreInfo& obj);
    ScoreInfo& operator =(const ScoreInfo& obj);

    QString Id() const;
    QString Name() const;
    int Score() const;

private:
    QString m_id;
    QString m_name;
    int m_score;
};

#endif // SCOREINFO_H
