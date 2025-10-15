#include "test_02.h"

test_02::test_02(quint16 test_id, QWidget *parent)
    : test(test_id, parent)
{
    init_UI();

    init_top_widget();

    init_middle_widget();

    init_footer_widget();
}

void test_02::init_UI()
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
    layout->setSpacing(1);
    layout->setContentsMargins(5, 5, 5, 5);

    setLayout(layout);
}

void test_02::init_top_widget()
{
    // 竖排排列
    QVBoxLayout* total_layout = new QVBoxLayout();

    // 第一排按钮横排排列
    QHBoxLayout* btn_layout = new QHBoxLayout();

    _btn_open_para    = createToolButton(":/icon/icon/open_file.svg",   "打开参数");
    _btn_save_para    = createToolButton(":/icon/icon/save_file.svg",   "保存参数");
    _btn_print_test   = createToolButton(":/icon/icon/print_file.svg",  "打印测试记录");

    _btn_up_para      = createToolButton(":/icon/icon/up.svg", "递增数据");
    _btn_down_para    = createToolButton(":/icon/icon/down.svg", "递减数据");
    _btn_reset_test   = createToolButton(":/icon/icon/data_recover.svg", "数据复位");
    _btn_start_test   = createToolButton(":/icon/icon/start.svg", "开始实验");
    _btn_end_test     = createToolButton(":/icon/icon/stop.svg", "停止实验");
    _btn_fdq          = createToolButton(":/icon/icon/chart_fdq.svg", "放大器");


    // 把按钮加到布局中
    btn_layout->addWidget(_btn_open_para);
    btn_layout->addWidget(_btn_save_para);
    btn_layout->addWidget(_btn_print_test);
    btn_layout->addWidget(_btn_up_para);
    btn_layout->addWidget(_btn_down_para);
    btn_layout->addWidget(_btn_reset_test);
    btn_layout->addWidget(_btn_start_test);
    btn_layout->addWidget(_btn_end_test);
    btn_layout->addWidget(_btn_fdq);

    total_layout->addLayout(btn_layout);
    _top_widget->setLayout(total_layout);
    _top_widget->setObjectName("topWidget");
}

void test_02::init_middle_widget()
{
    _middle_widget->setObjectName("middle_obj");
    QHBoxLayout* _h_layout = new QHBoxLayout();     // 总体layout

    QWidget* _centre_left_widget = new QWidget();       // 左侧操作widget
    _centre_left_widget->setObjectName("centre_left_widget");

    // 左侧layout
    QVBoxLayout* _centre_left_layout = new QVBoxLayout();

    // 左侧操作选择widget
    _ui_002 = new ui_002();
    _centre_left_layout->addWidget(_ui_002);

    // 左侧图表Widget

    _centre_left_widget->setLayout(_centre_left_layout);

    _h_layout->addWidget(_centre_left_widget);
    // _h_layout->addWidget(_ui_charts);
    // _h_layout->addWidget(_right_table_widget);
    _h_layout->setStretch(0, 20);   // top
    _h_layout->setStretch(1, 45);  // middle
    _h_layout->setStretch(2, 35);  // bottom

    _middle_widget->setLayout(_h_layout);
}



void test_02::init_footer_widget()
{

}
