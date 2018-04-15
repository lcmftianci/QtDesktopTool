#include "mainview.h"
#include "ui_mainview.h"
#include <QProcess>
#include <QObject>
#include <QTimer>
#include <QPixmap>
#include <QLabel>
#include <QApplication>
#include <QDesktopWidget>
#include <QLayoutItem>
#include <QClipboard>
#include <QScreen>
#include "timestamp.h"
#include <QCursor>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QDesktopServices>
#include <QStandardPaths>

MainView::MainView(QWidget *parent) :  QDialog(parent), ui(new Ui::MainView)
{
    ui->setupUi(this);

    m_pTimer = new QTimer();
    m_pLabel = new QLabel();
    m_pScreen = QGuiApplication::primaryScreen();
    QObject::connect(m_pTimer, SIGNAL(timeout()), this, SLOT(OnScreenCut()));
    //QObject::connect(ui->BtnStart, SIGNAL(clicked(bool)), this, StartProgram(bool));
    QObject::connect(ui->BtnStart, SIGNAL(clicked(bool)), this, SLOT(StartProgram(bool)));
    m_pTimer->start(1000/15);
}

MainView::~MainView()
{
    delete ui;
}

void MainView::StartProgram(bool bFlag)
{
    QString strLineEditText = ui->StartLineEdit->text().trimmed();
    QProcess *process = new QProcess;
    process->start(strLineEditText);
}

void MainView::OnScreenCut()
{
    timestramp time;
    //this->m_pix = QPixmap::grabWindow(QApplication::desktop()->winId());
    this->m_pix = m_pScreen->grabWindow(QApplication::desktop()->winId());
    m_pLabel->setScaledContents(true);
    m_pLabel->setPixmap(m_pix.scaled(ui->scrollArea->width(), ui->scrollArea->height()));
    ui->gridLayout->addWidget(m_pLabel, 0, 0, 1, 1);
    //pClipboard->setPixmap(m_pix);
}

void MainView::OnSavePic(bool bFlag)
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save File", QStandardPaths::writableLocation(QStandardPaths::PicturesLocation));
    this->m_pix.save(fileName);
}

void MainView::contextMenuEvent(QContextMenuEvent *e)
{
    QMenu *menu = new QMenu(this);
    QAction *action = new QAction(this);
    QAction *action1;
    QObject::connect(action, SIGNAL(triggered(bool)), this, SLOT(OnSavePic(bool)));
    action->setText("Save Picture");
    menu->addAction(action);
    menu->exec(QCursor::pos());
}
