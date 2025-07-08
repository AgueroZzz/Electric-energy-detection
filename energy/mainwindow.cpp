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

void MainWindow::init_ui()
{
    QMenuBar *menuBar = this->menuBar();
    QMenu *fileMenu = menuBar->addMenu("文件");
    fileMenu->addAction("打开");
    fileMenu->addAction("保存");
    fileMenu->addSeparator();
    fileMenu->addAction("退出");

    QMenu *editMenu = menuBar->addMenu("编辑");
    editMenu->addAction("复制");
    editMenu->addAction("粘贴");

    QSplitter *centralSplitter = new QSplitter(Qt::Horizontal, this);

    QDockWidget *leftDock = new QDockWidget("测试项目", this);
    QListWidget *testItems = new QListWidget();
    testItems->addItems({"测试项目1", "测试项目2", "测试项目3", "测试项目4"});
    leftDock->setWidget(testItems);
    this->addDockWidget(Qt::LeftDockWidgetArea, leftDock);

    QWidget *rightArea = new QWidget();
    QVBoxLayout *rightLayout = new QVBoxLayout(rightArea);

    // 右侧顶部可以添加一些控件
    QHBoxLayout *topRightLayout = new QHBoxLayout();
    topRightLayout->addWidget(new QLabel("操作区:"));
    topRightLayout->addStretch();
    topRightLayout->addWidget(new QPushButton("开始测试"));

    // 右侧主操作区
    QTextEdit *operationArea = new QTextEdit();
    operationArea->setPlaceholderText("这里是操作区域...");

    rightLayout->addLayout(topRightLayout);
    rightLayout->addWidget(operationArea);

    // 将右侧区域设置为中央部件
    this->setCentralWidget(rightArea);

    // 5. 设置窗口属性
    this->setWindowTitle("测试工具");
    this->resize(800, 600);
}
