#include "ui_table_002.h"
#include "ui_ui_table_002.h"

ui_table_002::ui_table_002(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_table_002)
{
    ui->setupUi(this);

    ui->tb_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_1->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_3->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

ui_table_002::~ui_table_002()
{
    delete ui;
}
