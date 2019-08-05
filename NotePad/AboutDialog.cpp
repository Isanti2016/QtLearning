#include "AboutDialog.h"
#include <QPixmap>
#include <QPalette>

CAboutDialog::CAboutDialog(/*QWidget *parent*/)  :
    QDialog(/*parent,*/NULL, Qt::WindowCloseButtonHint), m_logolbl(this), m_infoEidt(this), m_closeBtn(this), m_Contact_Info(this)
{
    QPixmap pm(":/Res/pic/Logo.png");
    pm = pm.scaled(120,120, Qt::KeepAspectRatio);

    m_logolbl.setPixmap(pm);
    m_logolbl.move(20,20);
    m_logolbl.resize(120,120);

    QPalette pClose = m_infoEidt.palette();
    pClose.setColor( QPalette::Active, QPalette::Base, palette().color(QPalette::Active, QPalette::Background) );
    pClose.setColor( QPalette::Inactive, QPalette::Base, palette().color( QPalette::Inactive, QPalette::Background ) );
    m_infoEidt.setPalette( pClose );
    m_infoEidt.setFrameStyle( QFrame::NoFrame );

    m_infoEidt.move(200, 20);
    m_infoEidt.resize(180,120);
    m_infoEidt.setReadOnly(true);
    m_infoEidt.insertPlainText("NotePad Project\nPlatform: Qt 5.2\n\nCopyright:W.B.B");

    m_Contact_Info.setText("Tele: 13018200271");
    m_Contact_Info.move(22, 150);

    m_closeBtn.setText("Close");
    m_closeBtn.move(275, 170);
    m_closeBtn.resize(100, 30);

    setFixedSize( 390, 220 );
    setWindowTitle( "About NotePad" );

    connect( &m_closeBtn, SIGNAL(clicked(bool)), this, SLOT(close()) );
}
