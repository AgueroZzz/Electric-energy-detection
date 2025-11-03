#include "ui_003.h"
#include "ui_ui_003.h"

ui_003::ui_003(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_003)
{
    ui->setupUi(this);
    ui->tb_fz_xw->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_fz_xw->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_test_deploy->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_test_deploy->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_krl->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_krl->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_result->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_result->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    _chart_001 = new ui_charts();
    _chart_002 = new ui_charts_002();

    QVBoxLayout* _chart_layout = new QVBoxLayout();
    _chart_layout->setContentsMargins(3, 3, 3, 3);
    _chart_layout->addWidget(_chart_001, 3);
    _chart_layout->addWidget(_chart_002, 2);
    ui->widget_charts->setLayout(_chart_layout);
}

ui_003::~ui_003()
{
    delete ui;
}
