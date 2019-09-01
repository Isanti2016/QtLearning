#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QToolBar>
#include <QPoint>
#include <QPainter>
#include <QList>
#include <QWidget>
#include <QPixmap>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum ShapeType
    {
        UnKnown = 1,
        EN_Shape_Type_Free,
        EN_Shape_Type_Line,
        EN_Shape_Type_Rect,
        EN_Shape_Type_RoundedRect,
        EN_Shape_Type_Ellipse,
    };

    struct DrawPara
    {
        ShapeType       m_enShapeType;
        QColor          m_color;
        mutable QList<QPoint>   m_vecPoint;

        DrawPara()
        {
            Clear();
        }
        void Clear()
        {
            m_enShapeType = UnKnown;
            m_color = QColor();
            m_vecPoint.clear();
        }

    };

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected slots:
   void OnOpen();
   void OnNew();
   void OnSave();
   void OnClear();
   void OnCaptureScreen();
   void OnShapeFreeType();
   void OnShapeLineType();
   void OnShapeRectType();
   void OnShapeRoundedRectType();
   void OnShapeEllipseType();
   void OnColor();

   void ChangeShapeTypeEnable( const QString& strShapeType );
   QAction* FindToolAction( const QString& strShapeType );
   QToolBar* ToolBar();

protected:
   void mousePressEvent(QMouseEvent *evt);
   void mouseMoveEvent(QMouseEvent *evt);
   void mouseReleaseEvent(QMouseEvent *evt);

   void paintEvent( QPaintEvent* evt );


private:
   QList<DrawPara> m_listDrawPara;
   DrawPara m_stuCurrentDrawPara;
   QWidget m_DrawDevice;
   QPixmap m_pMap;

   bool InitMenu();
   bool InitToolBar();
   bool InitFileItem( QToolBar* pToolBar );
   bool InitToolItem( QToolBar* pToolBar );
   bool InitViewItem( QToolBar* pToolBar );

   bool makeAction( QAction*& pAction, QMenu* pMenu, QString keyTip, int iShortKey );
   bool makeAction( QAction*& pAction, QToolBar* pMenu, QString keyTip, QString strIconPath );

   void AppendPoint( const QPoint& point );
   void Draw(QPainter& objPainter, const DrawPara& stuDrawPara);

};

#endif // MAINWINDOW_H
