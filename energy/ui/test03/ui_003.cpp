#include "ui_003.h"
#include "ui_ui_003.h"

ui_003::ui_003(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_003)
{
    ui->setupUi(this);
}

ui_003::~ui_003()
{
    delete ui;
}
