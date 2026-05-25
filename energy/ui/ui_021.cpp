#include "ui_021.h"
#include "ui_ui_021.h"

ui_021::ui_021(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_021)
{
    ui->setupUi(this);

    // ui->tb_sysj->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // ui->tb_sysj->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

ui_021::~ui_021()
{
    delete ui;
}
