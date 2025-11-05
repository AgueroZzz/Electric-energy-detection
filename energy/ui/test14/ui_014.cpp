#include "ui_014.h"
#include "ui_ui_014.h"

ui_014::ui_014(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_014)
{
    ui->setupUi(this);
}

ui_014::~ui_014()
{
    delete ui;
}
