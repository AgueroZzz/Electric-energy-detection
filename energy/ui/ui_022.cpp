#include "ui_022.h"
#include "ui_ui_022.h"

ui_022::ui_022(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_022)
{
    ui->setupUi(this);

    ui->tb_cssj->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_cssj->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

ui_022::~ui_022()
{
    delete ui;
}
