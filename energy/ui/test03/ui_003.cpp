#include "ui_003.h"
#include "ui_ui_003.h"

ui_003::ui_003(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_003)
{
    ui->setupUi(this);
    ui->tb_fz_xw->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_fz_xw->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_test_deploy->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_test_deploy->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_krl->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_krl->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_result->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_result->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

ui_003::~ui_003()
{
    delete ui;
}
