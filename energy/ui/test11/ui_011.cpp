#include "ui_011.h"
#include "ui_ui_011.h"

ui_011::ui_011(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_011)
{
    ui->setupUi(this);

    ui->tb_sy_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_sy_1->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_sy_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_sy_2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->dt_sj->setReadOnly(true);
    ui->dt_sj->setButtonSymbols(QAbstractSpinBox::NoButtons);

    // 创建定时器更新时间
    QTimer *current_timer = new QTimer(this);
    connect(current_timer, &QTimer::timeout, [&]() {
        ui->dt_sj->setDateTime(QDateTime::currentDateTime());
        ui->dt_sj->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
    });

    current_timer->start(1000);
}

ui_011::~ui_011()
{
    delete ui;
}
