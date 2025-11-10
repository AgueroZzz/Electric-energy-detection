#include "ui_025.h"
#include "ui_ui_025.h"

ui_025::ui_025(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_025)
{
    ui->setupUi(this);

    ui->tb_sycs->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_sycs->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_down_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_down_1->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_down_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_down_2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_down_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

ui_025::~ui_025()
{
    delete ui;
}
