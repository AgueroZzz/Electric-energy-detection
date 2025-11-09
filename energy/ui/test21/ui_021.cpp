#include "ui_021.h"
#include "ui_ui_021.h"

ui_021::ui_021(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_021)
{
    ui->setupUi(this);
}

ui_021::~ui_021()
{
    delete ui;
}
