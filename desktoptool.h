#ifndef DESKTOPTOOL_H
#define DESKTOPTOOL_H

#include <QDialog>
#include <QTimer>
#include <QPoint>
#include <QString>

class QMovie;
class QFileManager;
class MainView;

namespace Ui {
class DesktopTool;
}

class DesktopTool : public QDialog
{
    Q_OBJECT

public:
    explicit DesktopTool(QWidget *parent = 0);
    ~DesktopTool();

private:
    void ShowMessage(const char* str);
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);
    bool CheckDragRegion(const QPoint &pos);

private slots:
    void onMove();
    void onStay();
    void onClose();
    void OnTimerOut();

private:
    //Ui::QToolTips ui;
      QTimer * m_pShowTimer;
      QTimer * m_pStayTimer;
      QTimer * m_pCloseTimer;
      QPoint   m_point;
      int      m_nDesktopHeight;
      double   m_dTransparent;
      QMovie * m_movie;
      bool     m_bDragEnabled;
      QPoint   m_CurPos;
      QString  m_DesktopPath;
      QFileManager *m_pFileManager;
      MainView * m_pView;

protected:
      void mouseDoubleClickEvent(QMouseEvent *e);

private:
    Ui::DesktopTool *ui;
};

#endif // DESKTOPTOOL_H
