#include "ui_015.h"
#include "ui_ui_015.h"

ui_015::ui_015(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_015)
{
    ui->setupUi(this);
}

ui_015::~ui_015()
{
    delete ui;
}
