#include "ui_015.h"
#include "ui_ui_015.h"

ui_015::ui_015(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_015)
{
    ui->setupUi(this);

    ui->tb_blzd_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_blzd_1->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_blzd_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_blzd_2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_sysb_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_sysb_1->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

ui_015::~ui_015()
{
    delete ui;
}
