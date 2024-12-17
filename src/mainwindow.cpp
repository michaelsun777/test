#include "mainwindow.h"

#include <QCoreApplication>
#include <QDebug>
#include <QDir>

#include <QJsonDocument>
#include <QJsonValue>

#include <QMessageBox>
#include <QRandomGenerator>
#include <QCefContext.h>

#include <QCefView.h>


#define URL_ROOT "http://QCefViewDoc"
#define INDEX_URL URL_ROOT "/index.html"
#define TUTORIAL_URL URL_ROOT "/tutorial.html"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
//    , ui(new Ui::MainWindow)
{
    m_ui.setupUi(this);
    setupWindow();

    QDir dir = QCoreApplication::applicationDirPath();
    // QString webResourceDir = QDir::toNativeSeparators(dir.filePath("webres"));
    QString uri = QString("file://") + QDir::toNativeSeparators(dir.filePath("webres/QCefViewTestPage.html"));
    // QCefContext::instance()->addLocalFolderResource(webResourceDir, URL_ROOT);
    createRightCefView();

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    //Qt::WindowFlags flags = windowFlags();
    //flags = flags & ~Qt::FramelessWindowHint;
    //setWindowFlags(flags);

}

MainWindow::~MainWindow()
{
}

void MainWindow::createRightCefView()
{
    if (m_pRightCefViewWidget)
    {
        m_pRightCefViewWidget->deleteLater();
        m_pRightCefViewWidget = nullptr;
    }

    ///*
    // build settings for per QCefView
    QCefSetting setting;

#if CEF_VERSION_MAJOR < 100
    setting.setPlugins(false);
#endif

    setting.setWindowlessFrameRate(60);
    // setting.setBackgroundColor(QColor::fromRgba(qRgba(255, 255, 220, 255)));
    // setting.setBackgroundColor(QColor::fromRgb(0, 0, 255));
    setting.setBackgroundColor(Qt::lightGray);

    // create the QCefView widget and add it to the layout container
    m_pRightCefViewWidget = new CefViewWidget("https://map.baidu.com/", &setting, this);
    m_pRightCefViewWidget->resize(500, 500);    
    m_pRightCefViewWidget->setContextMenuPolicy(Qt::DefaultContextMenu);
    //m_ui.Container->layout()->addWidget(m_pRightCefViewWidget);

    m_layout = new QVBoxLayout(this);
    m_layout->addWidget(m_pRightCefViewWidget);

    //QString uri ="https://map.baidu.com/";
    //QCefView * cefViewWidget = new QCefView(uri, &setting, this);
    // QVBoxLayout *layout = new QVBoxLayout(this);
    // cefViewWidget->resize(500, 500);
    // layout->addWidget(cefViewWidget);
    // cefViewWidget->setContextMenuPolicy(Qt::DefaultContextMenu);
   

    // 

    // allow show context menu for both OSR and NCW mode
    
}

void MainWindow::setupWindow()
{
}


void MainWindow::resizeEvent(QResizeEvent *event)
{
    QSize newSize = event->size();

    m_pRightCefViewWidget->resize(newSize);

    QWidget::resizeEvent(event); 
}