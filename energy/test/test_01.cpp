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
    _btn_open_para = new QPushButton();        // 打开参数按钮
    _btn_open_para->setIcon(QIcon(":/iocn/icon/icon_btn_dkcs.svg"));
    _btn_open_para->setToolTip("打开参数");
    _btn_save_para = new QPushButton();        // 保存参数按钮
    _btn_save_para->setIcon(QIcon(":/iocn/icon/icon_btn_save.svg"));
    _btn_save_para->setToolTip("保存参数");
    _btn_print_test = new QPushButton();       // 打印测试记录
    _btn_print_test->setIcon(QIcon(":/iocn/icon/icon_btn_print.svg"));
    _btn_print_test->setToolTip("打印测试记录");

    _btn_power_calcu = new QPushButton();      // 功率计算仪表
    _btn_power_calcu->setIcon(QIcon(":/iocn/icon/icon_btn_power.svg"));
    _btn_power_calcu->setToolTip("功率计算仪表");
    _btn_shortout_calcu = new QPushButton();   // 短路计算
    _btn_shortout_calcu->setIcon(QIcon(":/iocn/icon/icon_btn_shortout.svg"));
    _btn_shortout_calcu->setToolTip("短路计算仪表");

    _btn_recover_para = new QPushButton();     // 恢复默认值
    _btn_recover_para->setIcon(QIcon(":/iocn/icon/icon_btn_recover.svg"));
    _btn_recover_para->setToolTip("恢复默认值");
    _btn_up_para = new QPushButton();          // 递增数据
    _btn_up_para->setIcon(QIcon(":/iocn/icon/icon_btn_up.svg"));
    _btn_up_para->setToolTip("递增数据");
    _btn_down_para = new QPushButton();          // 递减数据
    _btn_down_para->setIcon(QIcon(":/iocn/icon/icon_btn_down.svg"));
    _btn_down_para->setToolTip("递减数据");
    _btn_start_test = new QPushButton();       // 开始实验
    _btn_start_test->setIcon(QIcon(":/iocn/icon/icon_btn_start.svg"));
    _btn_start_test->setToolTip("开始实验");
    _btn_end_test = new QPushButton();       // 停止实验
    _btn_end_test->setIcon(QIcon(":/iocn/icon/icon_btn_stop.svg"));
    _btn_end_test->setToolTip("停止实验");
    _btn_reset_test = new QPushButton();     // 数据复位
    _btn_reset_test->setIcon(QIcon(":/iocn/icon/icon_btn_rset.svg"));
    _btn_reset_test->setToolTip("数据复位");

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

    // 第二排按钮横排排列
    QHBoxLayout* btn_chart_layout = new QHBoxLayout();

    _btn_symmetrical_output = new QPushButton("对称输出");   // 对称输出
    _btn_amplifier = new QPushButton("放大器");    // 放大器
    _btn_x = new QPushButton("背景X");    // 背景X
    _btn_round = new QPushButton("背景圆");       // 背景圆
    _btn_phase_component = new QPushButton("相分量");  // 相分量
    _btn_line_v = new QPushButton("线电压");   // 线电压
    _btn_order_component = new QPushButton("序分量"); // 序分量

    btn_chart_layout->addWidget(_btn_symmetrical_output);
    btn_chart_layout->addWidget(_btn_amplifier);
    btn_chart_layout->addWidget(_btn_x);
    btn_chart_layout->addWidget(_btn_round);
    btn_chart_layout->addWidget(_btn_phase_component);
    btn_chart_layout->addWidget(_btn_line_v);
    btn_chart_layout->addWidget(_btn_order_component);

    total_layout->addLayout(btn_layout);
    total_layout->addLayout(btn_chart_layout);
    _top_widget->setLayout(total_layout);
}

void test_01::init_middle_widget()
{
    QHBoxLayout* _h_layout = new QHBoxLayout();     // 总体layout

    QWidget* _centre_left_widget = new QWidget();       // 左侧操作widget
    QWidget* _centre_middle_widget = new QWidget();     // 中间图标widget
    QWidget* _centre_right_widget = new QWidget();      // 右侧数据表格widget

    // 左侧layout
    QVBoxLayout* _centre_left_layout = new QVBoxLayout();
    // 串口操作widget
    serial_opera* _opera = new serial_opera();
    // 点击选择widget
    QWidget* _check_widget = new QWidget();
    QGridLayout* check_layout = new QGridLayout(_check_widget);

    QGroupBox* _test_type_box = new QGroupBox("测试类型");
    QGroupBox* _test_open_box = new QGroupBox("开入量逻辑类型");
    QGroupBox* _test_box = new QGroupBox("测试选择");

    _check_test_action = new QCheckBox("测接点动作");          // 测试类型-测接点动作
    _check_test_action_back = new QCheckBox("测动作和返回");     // 测试类型-测动作和返回
    _check_open_and = new QCheckBox("逻辑与");             // 开入量逻辑类型-逻辑与
    _check_open_or = new QCheckBox("逻辑或");              // 开入量逻辑类型-逻辑或
    _check_mode_hand = new QCheckBox("手动");            // 测试-手动
    _check_mode_auto = new QCheckBox("自动");            // 测试-自动
    _check_mode_h_a = new QCheckBox("半自动");             // 测试-半自动
    _check_up = new QCheckBox("递增");                   // 测试-递增
    _check_down = new QCheckBox("递减");                 // 测试-递减

    QVBoxLayout* _test_type_layout = new QVBoxLayout();
    _test_type_layout->addWidget(_check_test_action);
    _test_type_layout->addWidget(_check_test_action_back);
    _test_type_box->setLayout(_test_type_layout);

    QVBoxLayout* _test_open_layout = new QVBoxLayout();
    _test_open_layout->addWidget(_check_open_and);
    _test_open_layout->addWidget(_check_open_or);
    _test_open_box->setLayout(_test_open_layout);

    QGridLayout* _test_layout = new QGridLayout();
    _test_layout->addWidget(_check_mode_hand, 0, 0);
    _test_layout->addWidget(_check_mode_auto, 0, 1);
    _test_layout->addWidget(_check_mode_h_a, 0, 2);
    _test_layout->addWidget(_check_up, 1, 0);
    _test_layout->addWidget(_check_down, 1, 1);

    // 设置每个选择group在选择widget中的排序
    check_layout->addWidget(_test_type_box, 0, 0);
    check_layout->addWidget(_test_open_box, 0, 1);
    check_layout->addWidget(_test_box, 1, 0);

    _centre_left_layout->addWidget(_opera);
    _centre_left_layout->addWidget(_check_widget);
    _centre_left_widget->setLayout(_centre_left_layout);

    _h_layout->addWidget(_centre_left_widget);
    _h_layout->addWidget(_centre_middle_widget);
    _h_layout->addWidget(_centre_right_widget);

    _centre_middle_widget->setStyleSheet("background-color: yellow;");
    _centre_right_widget->setStyleSheet("background-color: blue;");

    _h_layout->setStretch(0, 20);   // top
    _h_layout->setStretch(1, 45);  // middle
    _h_layout->setStretch(2, 35);  // bottom


    _middle_widget->setLayout(_h_layout);
}
