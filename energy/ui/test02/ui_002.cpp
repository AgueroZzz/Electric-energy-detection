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

void ui_002::init_table()
{
    QVBoxLayout* _table_layout = new QVBoxLayout();
    _chart_table_widget = new QTableWidget();   // 右侧表格
    _chart_table_widget->setRowCount(8);
    _chart_table_widget->setColumnCount(8);

    // 设置列标题
    QStringList headers;
    headers << "参量" << "有效值" << "变" << "步长" << "上限" << "相位" << "变" << "步长";
    _chart_table_widget->setHorizontalHeaderLabels(headers);
    // 表格美化
    _chart_table_widget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    _chart_table_widget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    _chart_table_widget->verticalHeader()->setVisible(false);
}
