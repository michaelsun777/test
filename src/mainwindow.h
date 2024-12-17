#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QHBoxLayout>


#include "ui_mainwindow.h"
#include "../3rd/QCefView/example/QCefViewTest/CefViewWidget.h"

// #include "/home/amplesky/work/test/cef_binary_132.0.4+ge3e90f9+chromium-132.0.6834.15_linux64_beta/include/cef_app.h"
// #include "/home/amplesky/work/test/cef_binary_132.0.4+ge3e90f9+chromium-132.0.6834.15_linux64_beta/include/cef_client.h"
// #include "/home/amplesky/work/test/cef_binary_132.0.4+ge3e90f9+chromium-132.0.6834.15_linux64_beta/include/wrapper/cef_message_router.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
  void createRightCefView();
  void setupWindow();
  void resizeEvent(QResizeEvent *event) override;

private:
    Ui::MainWindow m_ui;
    QVBoxLayout * m_layout;
    CefViewWidget* m_pRightCefViewWidget = nullptr;
};
#endif // MAINWINDOW_H
