#include "test_01.h"

test_01::test_01(quint16 test_id, QWidget *parent)
    : test(test_id, parent)
{
    init_UI();

    init_top_btn();

    init_middle_widget();
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

    setLayout(layout);
}

void test_01::init_top_btn()
{
    // 竖排排列
    QVBoxLayout* total_layout = new QVBoxLayout();

    // 第一排按钮横排排列
    QHBoxLayout* btn_layout = new QHBoxLayout();
    QPushButton* _btn_open_para = new QPushButton();        // 打开参数按钮
    _btn_open_para->setIcon(QIcon(":/iocn/icon/icon_btn_dkcs.svg"));
    _btn_open_para->setToolTip("打开参数");
    QPushButton* _btn_save_para = new QPushButton();        // 保存参数按钮
    _btn_save_para->setIcon(QIcon(":/iocn/icon/icon_btn_save.svg"));
    _btn_save_para->setToolTip("保存参数");
    QPushButton* _btn_print_test = new QPushButton();       // 打印测试记录
    _btn_print_test->setIcon(QIcon(":/iocn/icon/icon_btn_print.svg"));
    _btn_print_test->setToolTip("打印测试记录");

    QPushButton* _btn_power_calcu = new QPushButton();      // 功率计算仪表
    _btn_power_calcu->setIcon(QIcon(":/iocn/icon/icon_btn_power.svg"));
    _btn_power_calcu->setToolTip("功率计算仪表");
    QPushButton* _btn_shortout_calcu = new QPushButton();   // 短路计算
    _btn_shortout_calcu->setIcon(QIcon(":/iocn/icon/icon_btn_shortout.svg"));
    _btn_shortout_calcu->setToolTip("短路计算仪表");

    QPushButton* _btn_recover_para = new QPushButton();     // 恢复默认值
    _btn_recover_para->setIcon(QIcon(":/iocn/icon/icon_btn_recover.svg"));
    _btn_recover_para->setToolTip("恢复默认值");
    QPushButton* _btn_up_para = new QPushButton();          // 递增数据
    _btn_up_para->setIcon(QIcon(":/iocn/icon/icon_btn_up.svg"));
    _btn_up_para->setToolTip("递增数据");
    QPushButton* _btn_down_para = new QPushButton();          // 递减数据
    _btn_down_para->setIcon(QIcon(":/iocn/icon/icon_btn_down.svg"));
    _btn_down_para->setToolTip("递减数据");
    QPushButton* _btn_start_test = new QPushButton();       // 开始实验
    _btn_start_test->setIcon(QIcon(":/iocn/icon/icon_btn_start.svg"));
    _btn_start_test->setToolTip("开始实验");
    QPushButton* _btn_end_test = new QPushButton();       // 停止实验
    _btn_end_test->setIcon(QIcon(":/iocn/icon/icon_btn_stop.svg"));
    _btn_end_test->setToolTip("停止实验");
    QPushButton* _btn_reset_test = new QPushButton();     // 数据复位
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

    QPushButton* _btn_symmetrical_output = new QPushButton("对称输出");   // 对称输出
    QPushButton* _btn_amplifier = new QPushButton("放大器");    // 放大器
    QPushButton* _btn_x = new QPushButton("背景X");    // 背景X
    QPushButton* _btn_round = new QPushButton("背景圆");       // 背景圆
    QPushButton* _btn_phase_component = new QPushButton("相分量");  // 相分量
    QPushButton* _btn_line_v = new QPushButton("线电压");   // 线电压
    QPushButton* _btn_order_component = new QPushButton("序分量"); // 序分量

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
    QHBoxLayout* _h_layout = new QHBoxLayout();

    QWidget* _centre_left_widget = new QWidget();
    QWidget* _centre_middle_widget = new QWidget();
    QWidget* _centre_right_widget = new QWidget();

    _h_layout->addWidget(_centre_left_widget);
    _h_layout->addWidget(_centre_middle_widget);
    _h_layout->addWidget(_centre_right_widget);

    _centre_left_widget->setStyleSheet("background-color: lightgreen;");
    _centre_middle_widget->setStyleSheet("background-color: yellow;");
    _centre_right_widget->setStyleSheet("background-color: blue;");

    _h_layout->setStretch(0, 25);   // top
    _h_layout->setStretch(1, 50);  // middle0.
    _h_layout->setStretch(2, 25);  // bottom

    _middle_widget->setLayout(_h_layout);
}
