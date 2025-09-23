#include "mainwindow.h"
#include "test/test_02.h"
#include "ui_mainwindow.h"
#include "test/test_01.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setMinimumSize(1300,800);

    showMaximized();

    setWindowIcon(QIcon(":/icon/icon/app_icon.svg"));

    setWindowTitle("电力测试软件");

    // 测试项目工厂
    testCreators = {
        {0, [](quint16 id) { return new test_01(id); }},        // 三相交流实验
        {1, [](quint16 id) { return new test_02(id); }}
    };

    init_ui();

    _choose = new test_choose();
    QObject::connect(_choose, &test_choose::sig_test_pro_choose, this, &MainWindow::slot_test_pro_choose);
    _choose->show();
    _choose->raise();
    _choose->activateWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_test_pro_choose(quint16 test_id)
{
    qDebug() << "slot_test_pro_choose called with test_id:" << test_id;

    // 如果 test_id 相同，忽略
    if (test_id == _test_id) {
        qDebug() << "Same test_id, no change needed";
        return;
    }

    // 清理当前测试控件
    clearCurrentTest();

    // 创建新控件
    auto it = testCreators.find(test_id);
    if (it != testCreators.end()) {
        _test = it->second(test_id);
        _test->setMinimumSize(200, 200); // 确保控件有大小
        setCentralWidget(_test);
        qDebug() << "Test widget added for test_id:" << test_id;
        _test_id = test_id;
    } else {
        qDebug() << "Invalid test_id:" << test_id;
    }
}

void MainWindow::init_ui()
{
    // resize(1500, 900);
    setStyleSheet("QMainWindow { background-color: #EEF0ED; }");
    createMenuBar();
}

void MainWindow::createMenuBar()
{
    // 文件菜单
    fileMenu = menuBar()->addMenu("文件(&F)");
    fileMenu->addAction("新建(&N)");
    fileMenu->addAction("打开(&O)");
    fileMenu->addAction("保存(&S)");
    fileMenu->addSeparator();
    fileMenu->addAction("退出(&X)");

    // 测试选择
    testMenu = menuBar()->addMenu("项目(&P)");
    QAction* test_act_open = new QAction("打开测试", testMenu);
    QAction* test_act_close = new QAction("关闭测试", testMenu);
    testMenu->addAction(test_act_open);
    testMenu->addAction(test_act_close);
    QObject::connect(test_act_open, &QAction::triggered, this, [=](){
        _choose->show();
        _choose->raise();
        _choose->activateWindow();
    });


    // 编辑菜单
    editMenu = menuBar()->addMenu("编辑(&E)");
    editMenu->addAction("撤销(&U)");
    editMenu->addAction("重做(&R)");
    editMenu->addSeparator();
    editMenu->addAction("剪切(&T)");
    editMenu->addAction("复制(&C)");
    editMenu->addAction("粘贴(&P)");

    // 工具菜单
    toolMenu = menuBar()->addMenu("工具(&V)");
    toolMenu->addAction("工具栏");
    toolMenu->addAction("状态栏");

    // 帮助菜单
    helpMenu = menuBar()->addMenu("帮助(&H)");
    helpMenu->addAction("关于(&A)");
    helpMenu->addAction("帮助文档(&H)");
}

void MainWindow::clearCurrentTest()
{
    if (_test) {
        _test->close();
        _test->deleteLater();
        _test = nullptr;
        _test_id = -1;
        qDebug() << "Current test widget cleared";
    }
}
