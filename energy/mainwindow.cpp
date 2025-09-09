#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init_ui();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_test_pro_choose(quint16 test_id)
{
    switch (test_id) {
    case 1:
        break;
    default:
        break;
    }
}

void MainWindow::init_ui()
{
    resize(1200, 800);
    createMenuBar();

    createMainContent();
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
    QObject::connect(test_act_open, &QAction::triggered, this, [=](){
        if(_test == nullptr){

        }else{
            _test->deleteLater();
        }
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

void MainWindow::createMainContent()
{
    // 创建中央部件
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // 创建主垂直布局
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setSpacing(8);
    mainLayout->setContentsMargins(12, 12, 12, 12);

}
