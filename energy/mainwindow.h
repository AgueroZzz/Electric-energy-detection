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
#include "test/test_choose.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    enum index_tset{
        test_null = 0,              // 三相交流实验
        test_sxjlcs = 1,            // 三项直流实验
        test_sxzlcs,                // 交直流实验
        test_xbsy,                  // 谐波实验
        test_ztxl_I,                // 状态序列1
        test_ztxl_II,               // 状态序列2
        test_i_t,                   // i-t测试
        test_pl_gdz,                // 频率及高低周保护
        test_glfx_zk,               // 功率方向和阻抗
        test_zzcs_i,                // 整组测试I
        test_zzcs_ii,               // 整组测试II
        test_jl_lxbh,               // 距离和零序保护
        test_xlbhdzjy,              // 线路保护定值校验
        test_zktxcs,                // 阻抗特性试验
        test_cdbhsy,                // 差动保护
        test_cddz,                  // 差动定值
        test_cdjdq,                 // 差动继电器
        test_cdxb,                  // 差动谐波
        test_bztcs,                 // 备自投测试
        test_kqcs,                  // 快切
        test_tqsy,                  // 同期试验
    };

signals:
    void sig_test_pro_choose(quint16 test_id);

private slots:
    void slot_test_pro_choose(quint16 test_id);

private:
    Ui::MainWindow *ui;

    void init_ui();
    void createMenuBar();
    void createStatusBar();
    void clearCurrentTest(); // 清理当前测试控件

    // 菜单界面
    QMenu* fileMenu;
    QMenu* editMenu;
    QMenu* toolMenu;
    QMenu* helpMenu;
    QMenu* testMenu;

    QWidget *centralWidget;

    // 主界面Widget
    QWidget* headerWidget;

    QVBoxLayout *mainLayout;

    // 当前测试索引
    test* _test = nullptr;
    quint16 _test_id;

    // 测试控件工厂
    using TestCreator = std::function<test*(quint16)>;
    std::map<quint16, TestCreator> testCreators; // 映射 test_id 到创建函数

    // 功能选择界面
    test_choose* _choose = nullptr;
};



#endif // MAINWINDOW_H
