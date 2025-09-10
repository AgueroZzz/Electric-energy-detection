#include "test_choose.h"
#include "ui_test_choose.h"

test_choose::test_choose(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::test_choose)
{
    ui->setupUi(this);


    setWindowTitle("功能选择");
    setFixedSize(600, 800);
    setupUI();
    applyIndustrialStyle();
}

QString test_choose::getSelectedFunction() const
{
    if (listWidget->currentItem()) {
        return listWidget->currentItem()->text();
    }
    return QString();
}

test_choose::~test_choose()
{
    delete ui;
}

void test_choose::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *titleLabel = new QLabel("请选择实验功能:", this);
    titleLabel->setFont(QFont("Arial", 14, QFont::Bold));
    mainLayout->addWidget(titleLabel);

    listWidget = new QListWidget(this);
    listWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    QStringList functions = {
        "1.交流实验",
        "2.直流实验",
        "3.交直流实验",
        "4.谐波实验",
        "5.状态序列I",
        "6.状态序列II",
        "7.I-t特性",
        "8.频率及高低周",
        "9.功率方向-阻抗测试",
        "10.整组实验I",
        "11.整组实验II",
        "12.距离和零序保护",
        "13.线路保护",
        "14.阻抗特性",
        "15.差动保护",
        "16.差动定值",
        "17.差动继电器",
        "18.差动谐波",
        "19.备自投测试",
        "20.快切",
        "21.同期实验",
        "22.6-35KV线路综合保护",
        "23.功率振荡",
        "24.故障再现",
        "25.六相电流实验",
        "26.六相电压实验",
        "27.六相电压六相电流实验",
        "28.三相交流实验-按序分量输出"
    };

    listWidget->addItems(functions);
    listWidget->setCurrentRow(0);

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidget(listWidget);
    scrollArea->setWidgetResizable(true);
    mainLayout->addWidget(scrollArea);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *confirmButton = new QPushButton("确认", this);
    QObject::connect(confirmButton, &QPushButton::clicked, this, [=](){
        current_test_index = listWidget->currentRow();
        emit sig_test_pro_choose(current_test_index);
        close();
    });
    QPushButton *cancelButton = new QPushButton("取消", this);
    QObject::connect(cancelButton, &QPushButton::clicked, this, [=](){
        close();
    });

    buttonLayout->addStretch();
    buttonLayout->addWidget(confirmButton);
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addStretch();

    mainLayout->addLayout(buttonLayout);
}

void test_choose::applyIndustrialStyle()
{
    QString styleSheet = R"(
        QDialog {
            background-color: #F5F5F5;
            color: #000000;
        }
        QLabel {
            color: #000000;
            font-weight: bold;
        }
        QListWidget {
            background-color: #FFFFFF;
            border: 1px solid #CCCCCC;
            color: #000000;
            selection-background-color: #0078D4;
            selection-color: #FFFFFF;
            font-size: 14pt;
        }
        QPushButton {
            background-color: #E0E0E0;
            border: 1px solid #999999;
            color: #000000;
            padding: 8px 16px;
            font-size: 12pt;
            border-radius: 4px;
        }
        QPushButton:hover {
            background-color: #D0D0D0;
        }
        QPushButton:pressed {
            background-color: #C0C0C0;
        }
        QScrollArea {
            background-color: #F5F5F5;
            border: none;
        }
        QScrollBar:vertical {
            background: #E0E0E0;
            width: 12px;
            margin: 0px;
        }
        QScrollBar::handle:vertical {
            background: #0078D4;
            min-height: 20px;
            border-radius: 6px;
        }
        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            background: none;
        }
    )";
    setStyleSheet(styleSheet);

    QApplication::setStyle(QStyleFactory::create("Fusion"));
}
