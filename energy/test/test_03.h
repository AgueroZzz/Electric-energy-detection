#ifndef TEST__3_H
#define TEST__3_H

#include "test.h"
#include "ui/test03/ui_003.h"
#include "charts/ac_chart.h"
#include "charts/dc_chart.h"
#include "process/process_3.h"

// test03:三项交直流电流电压实验

class test_03 : public test
{
public:
    test_03(quint16 test_id, QWidget *parent = nullptr);

    inline t3_test_auto get_test_auto(QString name){
        if(name == "手动实验"){
            return t3_test_auto::test_hand;
        }else if(name == "自动增加"){
            return t3_test_auto::test_auto_up;
        }else{
            return t3_test_auto::test_auto_down;
        }
    }

    inline t3_test_type get_test_type(QString name){
        if(name == "动作停止"){
            return t3_test_type::action;
        }else{
            return t3_test_type::action_and_return;
        }
    }

public slots:
    void slot_frame_parse_result(const QStringList& result);

private:
    void init_UI();
    void init_top_widget();                     // 初始化顶部按钮
    void init_chart_widget();                   // 初始化图像
    void init_state_widget();                   // 初始化状态栏

    // 顶部/中部/底部Widget
    QWidget* _top_widget;
    ui_003* _ui_003;
    QWidget* _state_widget;
    ac_chart* _ac;
    dc_chart* _dc;

    // 顶部btn
    QToolButton* _btn_open_para;        // 打开参数按钮
    QToolButton* _btn_save_para;        // 保存参数按钮
    QToolButton* _btn_print_test;       // 打印测试记录
    QToolButton* _btn_serial_opera;     // 串口操作
    QToolButton* _btn_up_para;          // 递增数据
    QToolButton* _btn_down_para;          // 递减数据
    QToolButton* _btn_start_test;       // 开始实验
    QToolButton* _btn_end_test;       // 停止实验
    QButtonGroup* _btn_test_group;
    QToolButton* _btn_reset_test;     // 数据复位

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

    process_3* _process_3 = nullptr;

    serial_ui* _serial_ui;

    QSharedPointer<serial_port> _serialPort;        // 串口智能指针类

private slots:
    void slot_charts_refresh();
    void slot_test_start();
    void slot_test_stop();
};

#endif // TEST__3_H
