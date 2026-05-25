#include "ui_012.h"
#include "ui_ui_012.h"

ui_012::ui_012(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_012)
{
    ui->setupUi(this);

    ui->tb_csxm_result->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_csxm_result->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_jlbh_jddl->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_jlbh_jddl->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_jlbh_xjdl->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_jlbh_xjdl->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_lxbh_lx->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_lxbh_lx->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

ui_012::~ui_012()
{
    delete ui;
}
