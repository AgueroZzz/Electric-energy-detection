#include "ui_002.h"
#include "ui_ui_002.h"

ui_002::ui_002(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_002)
{
    ui->setupUi(this);
}

ui_002::~ui_002()
{
    delete ui;
}
