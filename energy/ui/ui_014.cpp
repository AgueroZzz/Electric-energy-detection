#include "ui_014.h"
#include "ui_ui_014.h"

ui_014::ui_014(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_014)
{
    ui->setupUi(this);

    ui->tb_kgl_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_kgl_1->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_ssgccssz->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_ssgccssz->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_sszkbj_result->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_sszkbj_result->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_sszxcssz->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_sszxcssz->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_syxm_sycssz->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_syxm_sycssz->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_syxm_uxfs->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_syxm_uxfs->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_zdcs_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_zdcs_1->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_zdcs_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_zdcs_2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

ui_014::~ui_014()
{
    delete ui;
}
