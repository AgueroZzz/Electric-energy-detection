#include "ui_024.h"
#include "ui_ui_024.h"

ui_024::ui_024(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_024)
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

ui_024::~ui_024()
{
    delete ui;
}
