#ifndef TEST__1_H
#define TEST__1_H

#include "test.h"
#include "ui/test01/ui_001.h"
#include "charts/ac_chart.h"
#include "global/led.h"

class test_01 : public test
{
public:
    test_01(quint16 test_id, QWidget *parent = nullptr);

private:
    void init_UI();
    void init_top_widget();                     // 初始化顶部按钮
    void init_chart_widget();                   // 初始化图像
    void init_state_widget();                   // 初始化状态栏

    // 顶部/中部/底部Widget
    QWidget* _top_widget;
    ui_001* _ui_001;
    ac_chart* _voltage;
    QWidget* _state_widget;

    // 顶部btn
    QToolButton* _btn_open_para;        // 打开参数按钮
    QToolButton* _btn_save_para;        // 保存参数按钮
    QToolButton* _btn_print_test;       // 打印测试记录
    QToolButton* _btn_power_calcu;      // 功率计算仪表
    QToolButton* _btn_shortout_calcu;   // 短路计算
    QToolButton* _btn_recover_para;     // 恢复默认值
    QToolButton* _btn_up_para;          // 递增数据
    QToolButton* _btn_down_para;          // 递减数据
    QToolButton* _btn_start_test;       // 开始实验
    QToolButton* _btn_end_test;       // 停止实验
    QToolButton* _btn_reset_test;     // 数据复位

    // 图标btn
    QToolButton* _chart_btn_dc;         // 对称输出
    QToolButton* _chart_btn_fdq;        // 放大器
    QToolButton* _chart_btn_x;          // 背景X
    QToolButton* _chart_btn_o;          // 背景o
    QToolButton* _chart_btn_xfl;        // 相分量
    QToolButton* _chart_btn_xdy;        // 线电压
    QToolButton* _chart_btn_xufl;       // 序分量

    // 开关量
    QLabel* _state_label;               // 状态
    QLabel* _runtime_second;            // 运行时间
    led* _led_A;
    led* _led_B;
    led* _led_C;
    led* _led_R;
    led* _led_a;
    led* _led_b;
    led* _led_c;

    // test interface
private slots:
    // void slot_test_start(quint16 test_id) override;
};

#endif // TEST__1_H
