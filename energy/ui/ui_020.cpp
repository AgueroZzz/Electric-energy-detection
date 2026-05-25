#include "ui_020.h"
#include "ui_ui_020.h"

ui_020::ui_020(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_020)
{
    ui->setupUi(this);

    ui->tb_cszt_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_cszt_1->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_cszt_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_cszt_2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_jszt_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_jszt_1->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_qhzt_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_qhzt_1->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_qhzt_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_qhzt_2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_qhzt_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_qhzt_3->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

ui_020::~ui_020()
{
    delete ui;
}
