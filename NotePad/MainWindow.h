#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QLabel>
#include <QPlainTextEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QPlainTextEdit objMainEditor;
    QLabel objStatusLabel;

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

public:
    static MainWindow* NewInstance();
    ~MainWindow();
};


#endif // MAINWINDOW_H
