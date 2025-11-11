#include "ui_001.h"
#include "ui_ui_001.h"

ui_001::ui_001(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_001)
{
    ui->setupUi(this);

    ui->tb_cl->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_cl->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_down_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_down_1->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_down_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_down_2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_down_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

ui_001::~ui_001()
{
    delete ui;
}
