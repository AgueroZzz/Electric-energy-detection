#include "ui_023.h"
#include "ui_ui_023.h"

ui_023::ui_023(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_023)
{
    ui->setupUi(this);

    ui->tb_kgl->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_kgl->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

ui_023::~ui_023()
{
    delete ui;
}
