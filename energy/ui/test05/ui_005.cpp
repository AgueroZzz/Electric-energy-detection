#include "ui_005.h"
#include "ui_ui_005.h"

ui_005::ui_005(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_005)
{
    ui->setupUi(this);

    ui->tb_sycs->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_sycs->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_kr->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_kr->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

ui_005::~ui_005()
{
    delete ui;
}
