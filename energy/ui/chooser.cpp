#include "chooser.h"
#include "ui_chooser.h"

chooser::chooser(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::chooser)
{
    ui->setupUi(this);
}

chooser::~chooser()
{
    delete ui;
}
