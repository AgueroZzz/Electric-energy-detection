#include "ui_008.h"
#include "ui_ui_008.h"

ui_008::ui_008(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_008)
{
    ui->setupUi(this);

    ui->tb_ddlbs->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_ddlbs->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_ddlbs_result->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_ddlbs_result->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_ddybs->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_ddybs->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_df_dt->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_df_dt->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_dv_dt->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_dv_dt->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_dzpl->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_dzpl->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_dzsj->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_dzsj->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

ui_008::~ui_008()
{
    delete ui;
}
