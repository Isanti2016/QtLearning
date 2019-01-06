#include "WidgetTest.h"
#include <QColorDialog>
#include <QFontDialog>
#include <QProgressDialog>
#include <QTextDocument>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/Qprinter>

#include <QDebug>

WidgetTest::WidgetTest(QWidget *parent) : QWidget(parent),
    FontDialogBtn(this), ProgressDialogBtn(this), PrintDialogBtn(this)
{
    FontDialogBtn.setText("Font Dialog");
    FontDialogBtn.move(20, 20);
    FontDialogBtn.resize(160, 30);

    ProgressDialogBtn.setText("Progeress Dialog");
    ProgressDialogBtn.move(20, 70);
    ProgressDialogBtn.resize(160, 30);

    PrintDialogBtn.setText("Print DialogBtn");
    PrintDialogBtn.move(20, 120);
    PrintDialogBtn.resize(160, 30);

    resize(200, 170);
    setFixedSize(200, 170);;

    connect( &FontDialogBtn, SIGNAL(clicked()), this, SLOT(FrontDialogBtn_Clicked()));
    connect( &ProgressDialogBtn, SIGNAL(clicked()), this, SLOT(ProgressDialogBtn_Clicked()));
    connect ( &PrintDialogBtn, SIGNAL(clicked()), this, SLOT(PrintDialogBtn_Clicked()));



}

WidgetTest::~WidgetTest()
{

}


void WidgetTest::FrontDialogBtn_Clicked()
{
    QFontDialog dlg(this);

    dlg.setWindowTitle("Font Dialog Test");
    dlg.setCurrentFont(QFont("Courier New", 10, QFont::Bold));

    if(dlg.exec() ==  QFontDialog::Accepted)
    {
        qDebug() << dlg.selectedFont();
    }
}

void WidgetTest::ProgressDialogBtn_Clicked()
{
    QProgressDialog dlg(this);

    dlg.setWindowTitle(" UpDating ...");
    dlg.setLabelText("Downloading update from server.");
    dlg.setMinimum(0);
    dlg.setMaximum(100);
    dlg.setValue(60);

    dlg.exec();


}

void WidgetTest::PrintDialogBtn_Clicked()
{
    QPrintDialog dlg(this);

    dlg.setWindowTitle("Print Dialog Test");

    if( dlg.exec() == QPrintDialog::Accepted )
    {
        QPrinter* pPrint = dlg.printer();

        QTextDocument td;

        td.setHtml(" <h1>Print html object test</h1> ");

        pPrint->setOutputFileName("D:\\test.pdf");

        td.print(pPrint);
    }
}
