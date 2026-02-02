// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <memory>
#include <QMenu>
#include <QMenuBar>
#include <QProcess>
#include <QMessageBox>
#include "test/test.h"
#include "ui/chooser.h"
#include "test/test_factory.h"
#include "serial/serial_ui.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void onTestChosen(quint16 testId);
    void onOpenTestChooser();
    void onCloseCurrentTest();

private:
    void initUi();
    void createMenus();
    void resetCurrentTest();
    void switchTest(quint16 testId);

    // ---------- UI ----------
    std::unique_ptr<Ui::MainWindow> ui;
    QMenu *fileMenu{}, *testMenu{}, *editMenu{}, *toolMenu{}, *helpMenu{};

    // ---------- 测试 ----------
    std::unique_ptr<test> currentTest_;
    quint16 currentTestId_ = std::numeric_limits<quint16>::max();

    // ---------- 选择器 ----------
    std::unique_ptr<chooser> chooser_;
};
#endif // MAINWINDOW_H
