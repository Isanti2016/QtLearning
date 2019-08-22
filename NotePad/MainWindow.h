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
#include <QSharedPointer>
#include "FindDialog.h"
#include "ReplaceDialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QPlainTextEdit m_objMainEditor;
    QLabel m_objStatusLabel;
    QString m_strPath;
    bool m_isTextChanged;
    QSharedPointer<FindDialog> m_pFindDlg;
    QSharedPointer<ReplaceDialog> m_pReplaceDlg;

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
    int  showQueryMessage(QString strMessage);
    QString saveCurrentData(QString strPath = "");
    void preEditChange();
    void openFileToEditor(QString strPath);
    QAction* findMenuBarAction(QString strAction);
    QAction* findToolBarAction(QString strAction);

    void StoreCfg();
    void ReadCfg();
    QToolBar* ToolBar();

protected:
    void closeEvent(QCloseEvent* event);
    void dragEnterEvent(QDragEnterEvent* e);    //托
    void dropEvent(QDropEvent* e);              //放

private slots:
    void OnFileOpen();
    void OnFileSave();
    void OnFileSavaAs();
    void OnFileNew();
    void OnTextChanged();
    void OnFilePrinter();
    void OnCursorPositionChange();
    void OnEditDelete();
    void OnFileExit();
    void OnEditFind();
    void OnEditReplace();

    void OnCopyAvailable(bool bAvailable);
    void OnUndoAvailable(bool bAvailable);
    void OnRedoAvailable(bool bAvailable);

    void OnEditGoto();
    void OnViewToolBar();
    void OnViewStatusBar();

    void OnFormatFont();
    void OnFormatWrap();
    void OnHelpManual();

    void OnHelpAbout();

public:
    static MainWindow* NewInstance();
    void OnCmdFileOpen( QString strPath );
    ~MainWindow();
};


#endif // MAINWINDOW_H
