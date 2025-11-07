#include "ui_019.h"
#include "ui_ui_019.h"

ui_019::ui_019(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_019)
{
    ui->setupUi(this);
}

ui_019::~ui_019()
{
    delete ui;
}
