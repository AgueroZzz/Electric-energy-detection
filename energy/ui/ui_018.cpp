#include "ui_018.h"
#include "ui_ui_018.h"

ui_018::ui_018(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_018)
{
    ui->setupUi(this);

    ui->tb_cycs->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_cycs->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_kgl->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_kgl->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_szxbhl->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_szxbhl->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

ui_018::~ui_018()
{
    delete ui;
}
