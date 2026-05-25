#include "ui_019.h"
#include "ui_ui_019.h"

ui_019::ui_019(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_019)
{
    ui->setupUi(this);

    ui->tb_dlsz->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_dlsz->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_dysz->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_dysz->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_syjg->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_syjg->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_zthcs_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_zthcs_1->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

ui_019::~ui_019()
{
    delete ui;
}
