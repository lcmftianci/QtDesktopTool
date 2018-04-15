#include "desktoptool.h"
#include "ui_desktoptool.h"
#include <QDesktopWidget>
#include <QDir>
#include <QDebug>
#include <QMovie>
#include <QMouseEvent>
#include <ShlObj.h>
#include <QStandardPaths>
#include "qfilemanager.h"
#include "mainwindow.h"
#include "mainview.h"

DesktopTool::DesktopTool(QWidget *parent) : QDialog(parent), ui(new Ui::DesktopTool)
{
    ui->setupUi(this);
 #ifdef NOUSE
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    //ui.setupUi(this);
    m_nDesktopHeight = QApplication::desktop()->height();
    m_dTransparent = 1.0;
    m_pShowTimer = new QTimer(this);
    m_pStayTimer = new QTimer(this);
    m_pCloseTimer = new QTimer(this);
    connect(m_pShowTimer, SIGNAL(timeout()), this, SLOT(onMove()));
    connect(m_pStayTimer, SIGNAL(timeout()), this, SLOT(onStay()));
    connect(m_pCloseTimer, SIGNAL(timeout()), this, SLOT(onClose()));
#endif

    m_bDragEnabled = false;
    m_CurPos = QPoint(0,0);

    setWindowFlags(windowFlags() | Qt::FramelessWindowHint| Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);

    qDebug() << "Current Puth" << QDir::currentPath();
    QPixmap pixmap("icon/StaticBb.jpg");
    ui->m_labelStatic->setPixmap(pixmap);

    m_movie = new QMovie("icon/DynamicBb.gif");
    ui->m_labelAnim->setMovie(m_movie);
    ui->m_labelAnim->hide();

    QTimer* timer = new QTimer;
    timer->setInterval(3000);
    timer->start();

    m_DesktopPath = "ABC";
    //WCHAR path[255];
    //SHGetSpecialFolderPath(0,path,CSIDL_DESKTOPDIRECTORY,0);
    //qDebug() << path;
    qDebug() << m_DesktopPath;

    m_DesktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    qDebug() << m_DesktopPath;
    //m_DesktopPath = QStandardPaths::standardLocations(QStandardPaths::DesktopLocation);
   // qDebug() << m_DesktopPath;


    //便利桌面文件夹
    m_pFileManager = new QFileManager();
    m_pFileManager->ReverseDir(m_DesktopPath);
    //ReverseDir(m_DesktopPath);

    connect(timer, SIGNAL(timeout()), this, SLOT(OnTimerOut()));
}

DesktopTool::~DesktopTool()
{
    delete ui;
}

void DesktopTool::ShowMessage(const char *str)
{
    ui->m_labelStatic->setStyleSheet("background-color:rgb(255,210,200);font:60px;color:blue");
    ui->m_labelStatic->setText(str);
    QRect rect = QApplication::desktop()->availableGeometry();
    m_point.setX(rect.width() - width());
    m_point.setY(rect.height() - height());
    move(m_point.x(), m_point.y());
    m_pShowTimer->start(5);
}

void DesktopTool::mouseMoveEvent(QMouseEvent *e)
{
    qDebug() << "mouseMove";
    if(m_bDragEnabled)
    {
        qDebug() << "mouseMouve Now";
        move(e->globalPos()+ m_CurPos);
    }
    qDebug() << "mouseMouve End";
}

void DesktopTool::mousePressEvent(QMouseEvent *e)
{
    if(CheckDragRegion(e->globalPos()))
    {
        m_bDragEnabled = true;
        m_CurPos = pos() - e->globalPos();
    }
}

void DesktopTool::mouseReleaseEvent(QMouseEvent *e)
{
    if(m_bDragEnabled)
    {
        m_bDragEnabled = false;
    }
}

bool DesktopTool::CheckDragRegion(const QPoint &pos)
{
    QPoint pt = pos;
    QRect rcWnd = geometry();
    qDebug() << "pos: " << pt << "geometry: " << rcWnd;
    pt.setX(pt.x() - rcWnd.left());
    pt.setY(pt.y() - rcWnd.top());
    int nW = rcWnd.width();
    int nH = rcWnd.height();
    QRect rcDrag(0, 0, nW, nH);
    if(rcDrag.contains(pt))
    {
        return true;
    }

    return false;
}

void DesktopTool::onMove()
{
    m_nDesktopHeight--;
    move(m_point.x(), m_nDesktopHeight);
    if (m_nDesktopHeight <= m_point.y())
    {
        m_pShowTimer->stop();
        m_pStayTimer->start(5000);
    }
}

void DesktopTool::onStay()
{
    m_pStayTimer->stop();
    m_pCloseTimer->start(100);
}

void DesktopTool::onClose()
{
    m_dTransparent -= 0.1;
    if (m_dTransparent <= 0.0)
    {
        m_pCloseTimer->stop();
        close();
    }
    else
    {
        setWindowOpacity(m_dTransparent);
    }
}

void DesktopTool::OnTimerOut()
{
    if(m_movie->state() == QMovie::Running)
    {
        m_movie->stop();
        ui->m_labelAnim->hide();
        ui->m_labelStatic->show();
    }
    else {
        m_movie->start();
        ui->m_labelAnim->show();
        ui->m_labelStatic->hide();
    }
}

void DesktopTool::mouseDoubleClickEvent(QMouseEvent *e)
{
   // MainWindow mw;
   // mw.show();
    //mw.set
    //mw.exec();
    //Sleep(10000);
    this->hide();
    MainView mv;
    mv.show();
    mv.exec();
    this->show();
}
