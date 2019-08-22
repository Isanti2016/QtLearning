#include "AppConfig.h"
#include <QFile>
#include <QDataStream>
#include <QIODevice>
#include <QApplication>

CAppConfig:: CAppConfig(QObject *parent) : QObject(parent)
{
    m_bValid = ReadCfg();
}

CAppConfig::CAppConfig(QFont objFont, bool bIsAutoWrap, bool bIsToolBarvisible, bool bIsStatusBarVisible, QRect objRect)
{
    m_objEditFont = objFont;
    m_bIsAutoWrap = bIsAutoWrap;
    m_bIsToolBarVisible = bIsToolBarvisible;
    m_bIsStatusBarVisible = bIsStatusBarVisible;
    m_objRect = objRect;

    m_bValid = true;
}

QFont CAppConfig::EditFont()
{
    return m_objEditFont;
}

bool CAppConfig::IsAutoWrap()
{
    return m_bIsAutoWrap;
}

bool CAppConfig::IsToolBarVisible()
{
    return m_bIsToolBarVisible;
}

bool CAppConfig::IsStatusBarVisible()
{
    return m_bIsStatusBarVisible;
}

QRect CAppConfig::AppRect()
{
    return m_objRect;
}

bool CAppConfig::IsValid()
{
    return m_bValid;
}

bool CAppConfig::StoreCfg()
{
    bool bRes = false;
    QFile objFile(QApplication::applicationDirPath() + "/AppCfg.config");

    if( objFile.open(QIODevice::WriteOnly) )
    {
        QDataStream objDataStream(&objFile);
        objDataStream.setVersion( QDataStream::Qt_5_11 );

        objDataStream << m_objEditFont;
        objDataStream << m_bIsAutoWrap;
        objDataStream << m_bIsToolBarVisible;
        objDataStream << m_bIsStatusBarVisible;
        objDataStream << m_objRect;
        bRes = true;

        objFile.close();
    }
    else
    {
        bRes = false;
    }

    return bRes;
}

bool CAppConfig::ReadCfg()
{
    bool bRes = false;
    QFile objFile(QApplication::applicationDirPath() + "/AppCfg.config");

    if( objFile.open(QIODevice::ReadOnly) )
    {
        QDataStream objDataStream(&objFile);
        objDataStream.setVersion( QDataStream::Qt_5_11 );

        objDataStream >> m_objEditFont;
        objDataStream >> m_bIsAutoWrap;
        objDataStream >> m_bIsToolBarVisible;
        objDataStream >> m_bIsStatusBarVisible;
        objDataStream >> m_objRect;
        bRes = true;

        objFile.close();
    }
    else
    {
        bRes = false;
    }

    return bRes;
}
