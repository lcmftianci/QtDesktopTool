#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QDialog>
#include <QTimer>

class QLabel;
class QPixmap;
class QLayoutItem;
class QClipboard;
class QScreen;

namespace Ui {
class MainView;
}

class MainView : public QDialog
{
    Q_OBJECT

public:
    explicit MainView(QWidget *parent = 0);
    ~MainView();

private slots:
    void StartProgram(bool bFlag);
    void OnScreenCut();
    void OnSavePic(bool bFlag);

protected:
    void contextMenuEvent(QContextMenuEvent *e);

private:
    QTimer *    m_pTimer;
    QPixmap     m_pix;
    QLabel  *   m_pLabel;
    QClipboard * pClipboard;
    QScreen *   m_pScreen;



private:
    Ui::MainView *ui;
};

#endif // MAINVIEW_H
