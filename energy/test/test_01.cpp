#include "test_01.h"
#include "serial/serial_opera.h"

test_01::test_01(quint16 test_id, QWidget *parent)
    : test(test_id, parent)
{
    init_UI();

    init_top_btn();

    init_middle_widget();

    set_qss();
}

void test_01::init_UI()
{
    _top_widget = new QWidget();
    _middle_widget = new QWidget();
    _footer_widget = new QWidget();

    // 设置背景颜色方便看效果
    _footer_widget->setStyleSheet("background-color: lightcoral;");

    // 垂直布局
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(_top_widget);
    layout->addWidget(_middle_widget);
    layout->addWidget(_footer_widget);

    // 设置比例（5 : 65 : 30）
    layout->setStretch(0, 5);   // top
    layout->setStretch(1, 65);  // middle0.
    layout->setStretch(2, 30);  // bottom

    // 设置组件之间的距离
    layout->setSpacing(5);
    layout->setContentsMargins(5, 5, 5, 5);

    setLayout(layout);
}

void test_01::init_top_btn()
{
    // 竖排排列
    QVBoxLayout* total_layout = new QVBoxLayout();

    // 第一排按钮横排排列
    QHBoxLayout* btn_layout = new QHBoxLayout();

    _btn_open_para    = createToolButton(":/iocn/icon/icon_btn_dkcs.svg",   "打开参数");
    _btn_save_para    = createToolButton(":/iocn/icon/icon_btn_save.svg",   "保存参数");
    _btn_print_test   = createToolButton(":/iocn/icon/icon_btn_print.svg",  "打印测试记录");

    _btn_power_calcu  = createToolButton(":/iocn/icon/icon_btn_power.svg",     "功率计算仪表");
    _btn_shortout_calcu = createToolButton(":/iocn/icon/icon_btn_shortout.svg","短路计算仪表");

    _btn_recover_para = createToolButton(":/iocn/icon/icon_btn_recover.svg", "恢复默认值");
    _btn_up_para      = createToolButton(":/iocn/icon/icon_btn_up.svg",      "递增数据");
    _btn_down_para    = createToolButton(":/iocn/icon/icon_btn_down.svg",    "递减数据");
    _btn_start_test   = createToolButton(":/iocn/icon/icon_btn_start.svg",   "开始实验");
    _btn_end_test     = createToolButton(":/iocn/icon/icon_btn_stop.svg",    "停止实验");
    _btn_reset_test   = createToolButton(":/iocn/icon/icon_btn_rset.svg",    "数据复位");

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
    QHBoxLayout* _h_layout = new QHBoxLayout();     // 总体layout

    QWidget* _centre_left_widget = new QWidget();       // 左侧操作widget
    _ui_charts = new ui_charts();     // 中间图标widget
    QWidget* _centre_right_widget = new QWidget();      // 右侧数据表格widget

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
    _h_layout->addWidget(_centre_right_widget);

    _centre_right_widget->setStyleSheet("background-color: blue;");

    _h_layout->setStretch(0, 20);   // top
    _h_layout->setStretch(1, 45);  // middle
    _h_layout->setStretch(2, 35);  // bottom


    _middle_widget->setLayout(_h_layout);
}
