// mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIcon>
#include <QDebug>

static constexpr QSize   kMinWindowSize{1300, 800};
static constexpr char const* kWindowTitle = QT_TR_NOOP("电力测试软件");
static constexpr char const* kAppIcon    = ":/icon/icon/app_icon.svg";

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

    chooser_->show();
}

MainWindow::~MainWindow() = default;

void MainWindow::initUi()
{
    // setStyleSheet(QStringLiteral("QMainWindow { background-color: #EEF0ED; }"));
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

    // ---------- 编辑 ----------
    editMenu = menuBar()->addMenu(tr("&编辑"));
    editMenu->addAction(tr("&Undo"));
    editMenu->addAction(tr("&Redo"));
    editMenu->addSeparator();
    editMenu->addAction(tr("Cu&t"));
    editMenu->addAction(tr("&Copy"));
    editMenu->addAction(tr("&Paste"));

    // ---------- 工具 ----------
    toolMenu = menuBar()->addMenu(tr("&工具"));
    toolMenu->addAction(tr("Toolbar"));
    toolMenu->addAction(tr("Status Bar"));

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
