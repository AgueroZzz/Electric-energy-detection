#include "ui_026.h"
#include "ui_ui_026.h"

ui_026::ui_026(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_026)
{
    ui->setupUi(this);

    ui->tb_sycs->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_sycs->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_down_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_down_1->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_down_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

ui_026::~ui_026()
{
    delete ui;
}
