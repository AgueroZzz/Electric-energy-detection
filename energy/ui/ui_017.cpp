#include "ui_017.h"
#include "ui_ui_017.h"

ui_017::ui_017(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_017)
{
    ui->setupUi(this);

    ui->tb_result->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_result->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

ui_017::~ui_017()
{
    delete ui;
}
