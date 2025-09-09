#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <QDockWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QGroupBox>

#include "test/test.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void slot_test_pro_choose(quint16 test_id);

private:
    Ui::MainWindow *ui;

    void init_ui();
    void createMenuBar();
    void createStatusBar();
    void createMainContent();

    // 菜单界面
    QMenu* fileMenu;
    QMenu* editMenu;
    QMenu* toolMenu;
    QMenu* helpMenu;
    QMenu* testMenu;

    // 主界面Widget
    QWidget* headerWidget;

    // 当前测试索引
    test* _test = nullptr;
};

#endif // MAINWINDOW_H
