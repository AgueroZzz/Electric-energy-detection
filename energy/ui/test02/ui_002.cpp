#include "ui_002.h"
#include "ui_ui_002.h"

ui_002::ui_002(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_002)
{
    ui->setupUi(this);

    init_UI();
}

ui_002::~ui_002()
{
    delete ui;
}

void ui_002::init_UI()
{
    QVBoxLayout* layout = new QVBoxLayout();
    _opera = new serial_opera();
    layout->addWidget(_opera);
    ui->serial_widget->setLayout(layout);

    ui->all_layout->setStretch(0, 2);
    ui->all_layout->setStretch(1, 2);
    ui->all_layout->setStretch(3, 6);
}
