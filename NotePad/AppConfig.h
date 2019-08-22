#ifndef _APPCONFIG_H
#define _APPCONFIG_H

#include <QObject>
#include <QFont>
#include <QRect>


class CAppConfig: public QObject
{
    Q_OBJECT
public:
    explicit CAppConfig(QObject *parent = 0);
    explicit CAppConfig(QFont objFont, bool bIsAutoWrap, bool bIsToolBarvisible, bool bIsStatusBarVisible, QRect objRect);
    QFont EditFont();
    bool IsAutoWrap();
    bool IsToolBarVisible();
    bool IsStatusBarVisible();
    QRect AppRect();
    bool IsValid();

    bool StoreCfg();

public slots:

private:
    QFont m_objEditFont;
    bool m_bIsAutoWrap;
    bool m_bIsToolBarVisible;
    bool m_bIsStatusBarVisible;
    QRect m_objRect;
    bool m_bValid;

    bool ReadCfg();

};

#endif // _APPCONFIG_H
