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

    QVBoxLayout* _table_layout = new QVBoxLayout();
    _chart_table_widget = new QTableWidget();   // 右侧表格
    _chart_table_widget->setRowCount(6);
    _chart_table_widget->setColumnCount(5);
    // 设置列标题
    QStringList headers;
    headers << "参量" << "有效值" << "变" << "步长" << "上限";
    _chart_table_widget->setHorizontalHeaderLabels(headers);

    // 表格美化
    _chart_table_widget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // _chart_table_widget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    _chart_table_widget->verticalHeader()->setVisible(false);

    _table_layout->addWidget(_chart_table_widget);
    ui->gp_table->setLayout(_table_layout);
    ui->gp_table->setMinimumHeight(400);
    ui->gp_table->setMinimumWidth(750);
}

void ui_002::init_table()
{
    QStringList rows;
    rows << "UA" << "UB" << "UC" << "IA" << "IB" << "IC";
    for(int row = 0; row < rows.size(); ++row){
        qDebug() << rows[row];
        QLabel* label = new QLabel(rows[row]);
        QCheckBox* b_1 = new QCheckBox();
        QWidget *container_1 = new QWidget();
        QHBoxLayout *layout_1 = new QHBoxLayout(container_1);
        layout_1->addWidget(b_1);
        layout_1->setAlignment(Qt::AlignCenter);
        b_1->setCheckState(Qt::Unchecked);
        _chart_table_widget->setCellWidget(row, 0, label);
        _chart_table_widget->setCellWidget(row, 2, container_1);
    }

    // 设置统一的固定行高
    int fixedRowHeight = 60; // 根据你的需求调整
    for (int i = 0; i < _chart_table_widget->rowCount(); ++i) {
        _chart_table_widget->setRowHeight(i, fixedRowHeight);
    }
}
