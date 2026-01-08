// mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serial/serial_port.h"
#include <QIcon>
#include <QDebug>

static constexpr QSize   kMinWindowSize{1300, 800};
static constexpr char const* kWindowTitle = QT_TR_NOOP("电力测试软件");
static constexpr char const* kAppIcon    = ":/icon/icon/app_icon.svg";

serial_port* _serial = nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(std::make_unique<Ui::MainWindow>())
{
    ui->setupUi(this);

    setMinimumSize(kMinWindowSize);
    setWindowIcon(QIcon(kAppIcon));
    setWindowTitle(tr(kWindowTitle));

    initUi();
    chooser_ = std::make_unique<chooser>();
    connect(chooser_.get(), &chooser::sig_test_pro_choose, this, &MainWindow::onTestChosen);

    chooser_->setWindowFlags(chooser_->windowFlags() | Qt::WindowStaysOnTopHint);
    chooser_->show();

    // 在此处初始化全局串口对象
    _serial = new serial_port();
    _serial->_thread.start();

    showMaximized();
    _serial_ui = new serial_ui();
}

MainWindow::~MainWindow() = default;

void MainWindow::initUi()
{
    createMenus();
}

void MainWindow::createMenus()
{
    // ---------- 文件 ----------
    fileMenu = menuBar()->addMenu(tr("&文件"));
    fileMenu->addAction(tr("&新建"),  this, [](){ /*TODO*/ });
    fileMenu->addAction(tr("&打开"), this, [](){ /*TODO*/ });
    fileMenu->addAction(tr("&保存"), this, [](){ /*TODO*/ });
    fileMenu->addSeparator();
    fileMenu->addAction(tr("&退出"), qApp, &QApplication::quit);

    // ---------- 项目 ----------
    testMenu = menuBar()->addMenu(tr("&项目"));
    testMenu->addAction(tr("&打开测试项目"), this, &MainWindow::onOpenTestChooser);
    testMenu->addAction(tr("&关闭测试项目"), this, &MainWindow::onCloseCurrentTest);

    // ---------- 串口操作 ----------
    serialMenu = menuBar()->addMenu(tr("&串口"));
    serialMenu->addAction(tr("&串口设置"), this, &MainWindow::onSerialChosen);

    // ---------- 编辑 ----------
    editMenu = menuBar()->addMenu(tr("&编辑"));
    editMenu->addAction(tr("&Undo"));
    editMenu->addAction(tr("&Redo"));
    editMenu->addSeparator();
    editMenu->addAction(tr("Cu&t"));
    editMenu->addAction(tr("&Copy"));
    editMenu->addAction(tr("&Paste"));

    // ---------- 工具 ----------
    toolMenu = menuBar()->addMenu(tr("&系统工具"));
    QMap<QString, QString> tools = {
        {tr("&计算器"), "calc.exe"},
        {tr("&放大镜"), "magnify.exe"},
        {tr("&记事本"), "notepad.exe"},
        {tr("&图画"), "mspaint.exe"}
    };

    for (auto it = tools.begin(); it != tools.end(); ++it) {
        QAction *action = toolMenu->addAction(it.key());
        QString toolPath = it.value();
        connect(action, &QAction::triggered, this, [toolPath]() {
            QProcess::startDetached(toolPath);
        });
    }

    // ---------- 帮助 ----------
    helpMenu = menuBar()->addMenu(tr("&帮助"));
    helpMenu->addAction(tr("&About"));
    helpMenu->addAction(tr("&Help Doc"));
}

void MainWindow::onOpenTestChooser()
{
    chooser_->show();
    chooser_->raise();
    chooser_->activateWindow();
}

void MainWindow::onCloseCurrentTest()
{
    resetCurrentTest();
}

void MainWindow::resetCurrentTest()
{
    if (currentTest_) {
        currentTest_->close();
        currentTest_.reset();
        setCentralWidget(nullptr);
        currentTestId_ = std::numeric_limits<quint16>::max();
    }
}

void MainWindow::onTestChosen(quint16 testId)
{
    if (testId == currentTestId_) return;

    resetCurrentTest();
    switchTest(testId);
}

void MainWindow::onSerialChosen()
{
    _serial_ui->show();
    _serial_ui->raise();
    _serial_ui->activateWindow();
}

void MainWindow::switchTest(quint16 testId)
{
    const auto &factory = TestFactory::instance();
    auto it = factory.find(testId);
    if (it == factory.end()) {
        qWarning() << "No creator for test_id:" << testId;
        return;
    }

    currentTest_.reset(it.value()(testId));
    currentTest_->setMinimumSize(200, 200);
    setCentralWidget(currentTest_.get());
    currentTestId_ = testId;

    qDebug() << "Test widget added for test_id:" << testId;
}
