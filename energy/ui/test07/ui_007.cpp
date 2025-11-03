#include "ui_007.h"
#include "ui_ui_007.h"

ui_007::ui_007(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_007)
{
    ui->setupUi(this);

    ui->tb_result->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_result->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_txdy->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_txdy->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_kglsz->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_kglsz->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

ui_007::~ui_007()
{
    delete ui;
}
