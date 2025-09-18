#ifndef TEST__1_H
#define TEST__1_H

#include "test.h"
#include "ui/test01/ui_001.h"

class test_01 : public test
{
public:
    test_01(quint16 test_id, QWidget *parent = nullptr);

private:
    void init_UI();

    void init_top_btn();                        // 初始化顶部按钮
    void init_middle_widget();                  // 初始化中间widget
    void init_middle_left_down_widget();        // 初始化中间-左侧-底部widget
    void init_radar_charts();                   // 初始化雷达图

    // 顶部/中部/底部Widget
    QWidget* _top_widget;
    QWidget* _middle_widget;
    QWidget* _footer_widget;

    // 顶部btn
    QPushButton* _btn_open_para;        // 打开参数按钮
    QPushButton* _btn_save_para;        // 保存参数按钮
    QPushButton* _btn_print_test;       // 打印测试记录
    QPushButton* _btn_power_calcu;      // 功率计算仪表
    QPushButton* _btn_shortout_calcu;   // 短路计算
    QPushButton* _btn_recover_para;     // 恢复默认值
    QPushButton* _btn_up_para;          // 递增数据
    QPushButton* _btn_down_para;          // 递减数据
    QPushButton* _btn_start_test;       // 开始实验
    QPushButton* _btn_end_test;       // 停止实验
    QPushButton* _btn_reset_test;     // 数据复位

    QPushButton* _btn_symmetrical_output;   // 对称输出
    QPushButton* _btn_amplifier;    // 放大器
    QPushButton* _btn_x;    // 背景X
    QPushButton* _btn_round;       // 背景圆
    QPushButton* _btn_phase_component;  // 相分量
    QPushButton* _btn_line_v;   // 线电压
    QPushButton* _btn_order_component; // 序分量

    ui_001* _ui_001;                        // 左侧窗口测试类型ui

};

#endif // TEST__1_H
