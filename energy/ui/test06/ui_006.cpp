#include "ui_006.h"
#include "ui_ui_006.h"

ui_006::ui_006(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_006)
{
    ui->setupUi(this);

    ui->tb_sycs->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_sycs->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_kr->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_kr->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

ui_006::~ui_006()
{
    delete ui;
}
