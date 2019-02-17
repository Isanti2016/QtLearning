#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QLabel>
#include <QPlainTextEdit>
#include <QFileDialog>
#include <QString>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QPlainTextEdit m_objMainEditor;
    QLabel m_objStatusLabel;
    QString m_strPath;

    MainWindow();
    MainWindow(const MainWindow&);
    MainWindow &operator= (const MainWindow&);

    bool construct();
    bool initMenuBar();
    bool initToolBar();
    bool initStatusBar();
    bool initMainEditor();

    bool initFileMenu(QMenuBar* pMb);
    bool initEditMenu(QMenuBar* pMb);
    bool initFormatMenu(QMenuBar* pMb);
    bool initViewMenu(QMenuBar* pMb);
    bool initHelpMenu(QMenuBar* pMb);

    bool initFileToolItem(QToolBar* pTb);
    bool initEditorToolItem(QToolBar* pTb);
    bool initFormatToolItem(QToolBar* pTb);
    bool initViewToolItem(QToolBar* pTb);

    bool makeAction(QAction*& pAction, QWidget* pParent, QString text, int key);
    bool makeAction(QAction*& pAction, QWidget* pParent, QString strTip, QString strIconPath);

    QString showFileDialog(QFileDialog::AcceptMode OpenMode,  QString strTitle);
    void showErrorMessage(QString strMessage);

private slots:
    void OnFileOpen();
    void OnFileSave();
    void OnFileSavaAs();

public:
    static MainWindow* NewInstance();
    ~MainWindow();
};


#endif // MAINWINDOW_H
