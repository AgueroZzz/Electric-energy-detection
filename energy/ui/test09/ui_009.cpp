#include "ui_009.h"
#include "ui_ui_009.h"

ui_009::ui_009(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_009)
{
    ui->setupUi(this);
}

ui_009::~ui_009()
{
    delete ui;
}
