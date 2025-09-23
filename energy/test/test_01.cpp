#include "test_01.h"
#include "serial/serial_opera.h"

test_01::test_01(quint16 test_id, QWidget *parent)
    : test(test_id, parent)
{
    init_UI();

    init_top_btn();

    init_middle_widget();

    init_footer_widget();

    set_qss();
}

void test_01::init_UI()
{
    _top_widget = new QWidget();
    _middle_widget = new QWidget();
    _footer_widget = new QWidget();

    // 垂直布局
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(_top_widget);
    layout->addWidget(_middle_widget);
    layout->addWidget(_footer_widget);

    // 设置比例（5 : 65 : 30）
    layout->setStretch(0, 5);   // top
    layout->setStretch(1, 65);  // middle.
    layout->setStretch(2, 30);  // bottom

    // 设置组件之间的距离
    layout->setSpacing(2);
    layout->setContentsMargins(5, 5, 5, 5);

    setLayout(layout);
}

void test_01::init_top_btn()
{
    // 竖排排列
    QVBoxLayout* total_layout = new QVBoxLayout();

    // 第一排按钮横排排列
    QHBoxLayout* btn_layout = new QHBoxLayout();

    _btn_open_para    = createToolButton(":/icon/icon/open_file.svg",   "打开参数");
    _btn_save_para    = createToolButton(":/icon/icon/save_file.svg",   "保存参数");
    _btn_print_test   = createToolButton(":/icon/icon/print_file.svg",  "打印测试记录");

    _btn_power_calcu  = createToolButton(":/icon/icon/power_calc.svg",     "功率计算仪表");
    _btn_shortout_calcu = createToolButton(":/icon/icon/short_calc.svg","短路计算仪表");

    _btn_recover_para = createToolButton(":/icon/icon/recover.svg", "恢复默认值");
    _btn_up_para      = createToolButton(":/icon/icon/up.svg",      "递增数据");
    _btn_down_para    = createToolButton(":/icon/icon/down.svg",    "递减数据");
    _btn_start_test   = createToolButton(":/icon/icon/start.svg",   "开始实验");
    _btn_end_test     = createToolButton(":/icon/icon/stop.svg",    "停止实验");
    _btn_reset_test   = createToolButton(":/icon/icon/data_recover.svg",    "数据复位");

    // 把按钮加到布局中
    btn_layout->addWidget(_btn_open_para);
    btn_layout->addWidget(_btn_save_para);
    btn_layout->addWidget(_btn_print_test);
    btn_layout->addWidget(_btn_power_calcu);
    btn_layout->addWidget(_btn_shortout_calcu);
    btn_layout->addWidget(_btn_recover_para);
    btn_layout->addWidget(_btn_up_para);
    btn_layout->addWidget(_btn_down_para);
    btn_layout->addWidget(_btn_start_test);
    btn_layout->addWidget(_btn_end_test);
    btn_layout->addWidget(_btn_reset_test);

    total_layout->addLayout(btn_layout);
    _top_widget->setLayout(total_layout);
}

void test_01::init_middle_widget()
{
    _middle_widget->setObjectName("middle_obj");
    QHBoxLayout* _h_layout = new QHBoxLayout();     // 总体layout

    QWidget* _centre_left_widget = new QWidget();       // 左侧操作widget
    _ui_charts = new ui_charts();     // 中间图标widget

    _chart_table_widget = new QTableWidget();   // 右侧表格
    _chart_table_widget->setRowCount(8);
    _chart_table_widget->setColumnCount(8);

    // 设置列标题
    QStringList headers;
    headers << "参量" << "有效值" << "变" << "步长" << "上限" << "相位" << "变" << "步长";
    _chart_table_widget->setHorizontalHeaderLabels(headers);

    // 设置行标题
    QStringList rows;
    rows << "UA" << "UB" << "UC" << "IA" << "IB" << "IC" << "Ux" << "Hz";
    _chart_table_widget->setVerticalHeaderLabels(rows);

    // 表格美化
    _chart_table_widget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    _chart_table_widget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);   // 行等高

    // 左侧layout
    QVBoxLayout* _centre_left_layout = new QVBoxLayout();
    // 串口操作widget
    serial_opera* _opera = new serial_opera();

    _ui_001 = new ui_001();

    _centre_left_layout->addWidget(_opera);
    _centre_left_layout->addWidget(_ui_001);
    _centre_left_widget->setLayout(_centre_left_layout);

    _h_layout->addWidget(_centre_left_widget);
    _h_layout->addWidget(_ui_charts);
    _h_layout->addWidget(_chart_table_widget);
    _h_layout->setStretch(0, 20);   // top
    _h_layout->setStretch(1, 45);  // middle
    _h_layout->setStretch(2, 35);  // bottom


    _middle_widget->setLayout(_h_layout);

}

void test_01::init_footer_widget()
{
    QHBoxLayout* _foot_table_layout = new QHBoxLayout();

    _chart_foot_left_widget = new QTableWidget();
    _chart_foot_middle_widget = new QTableWidget();
    _chart_foot_right_widget = new QTableWidget();

    // 左部
    _chart_foot_left_widget->setRowCount(9);
    _chart_foot_left_widget->setColumnCount(3);
    QStringList left_headers;
    left_headers << "参量" << "幅值" << "相位";
    _chart_foot_left_widget->setHorizontalHeaderLabels(left_headers);
    QStringList left_rows;
    left_rows << "UAB" << "UBC" << "UCA" << "Uo" << "U+" << "U-" << "Io" << "I+" << "I-";
    _chart_foot_left_widget->setVerticalHeaderLabels(left_rows);
    _chart_foot_left_widget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    _chart_foot_left_widget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);   // 行等高

    // 中部
    // 设置行列数
    _chart_foot_middle_widget->setRowCount(7);
    _chart_foot_middle_widget->setColumnCount(3);

    // 设置列头
    QStringList middle_headers;
    middle_headers << "开入量" << "动作时间" << "返回时间";
    _chart_foot_middle_widget->setHorizontalHeaderLabels(middle_headers);

    // 设置行头
    QStringList middle_rows;
    middle_rows << "A" << "B" << "C" << "R" << "a" << "b" << "c";

    // 使用自定义的复选框行头
    auto *header = new CheckBoxHeader(Qt::Vertical, _chart_foot_middle_widget);
    _chart_foot_middle_widget->setVerticalHeader(header);

    // 设置行头标签
    _chart_foot_middle_widget->setVerticalHeaderLabels(middle_rows);

    _chart_foot_middle_widget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    _chart_foot_middle_widget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);   // 行等高

    // 右部
    _chart_foot_right_widget->setRowCount(7);
    _chart_foot_right_widget->setColumnCount(4);
    QStringList right_headers;
    right_headers << "参量" << "动作" << "返回" << "返回系数";
    _chart_foot_right_widget->setHorizontalHeaderLabels(right_headers);
    QStringList right_rows;
    right_rows << "UA" << "UB" << "UC" << "IA" << "IB" << "IC" << "Ux";
    _chart_foot_right_widget->setVerticalHeaderLabels(right_rows);
    _chart_foot_right_widget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    _chart_foot_right_widget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);   // 行等高

    _foot_table_layout->addWidget(_chart_foot_left_widget, 0);
    _foot_table_layout->addWidget(_chart_foot_middle_widget, 1);
    _foot_table_layout->addWidget(_chart_foot_right_widget, 2);

    _footer_widget->setLayout(_foot_table_layout);
}
