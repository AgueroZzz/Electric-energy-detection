#include "ui_001.h"
#include "ui_ui_001.h"

ui_001::ui_001(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_001)
{
    ui->setupUi(this);
    ui->all_layout->setStretch(0, 2);
    ui->all_layout->setStretch(1, 2);
    ui->all_layout->setStretch(3, 6);
}

ui_001::~ui_001()
{
    delete ui;
}
