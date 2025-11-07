#include "ui_013.h"
#include "ui_ui_013.h"

ui_013::ui_013(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_013)
{
    ui->setupUi(this);

    ui->tb_csxm_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_csxm_1->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

ui_013::~ui_013()
{
    delete ui;
}
