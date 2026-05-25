#include "ui_016.h"
#include "ui_ui_016.h"

ui_016::ui_016(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_016)
{
    ui->setupUi(this);

    ui->tb_cs_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_cs_1->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

ui_016::~ui_016()
{
    delete ui;
}
