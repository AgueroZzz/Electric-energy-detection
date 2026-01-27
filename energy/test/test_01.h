#ifndef TEST__1_H
#define TEST__1_H

#include "test.h"
#include "ui/test01/ui_001.h"
#include "charts/ac_chart.h"
#include "global/led.h"
#include "process/process_1.h"


class test_01 : public test
{
public:
    test_01(quint16 test_id, QWidget *parent = nullptr);

    ~test_01(){
        if (_process_1) {
            _process_1->slot_stop();
        }
        if (_serialPort) {
            if (_serialPort->_serial_status == index_serial_status::serial_on) {
                _serialPort->slot_serial_opera(index_serial_status::serial_off, {});
            }
            if (_serialPort->_thread.isRunning()) {
                _serialPort->_thread.quit();

                if (!_serialPort->_thread.wait(3000)) {
                    qWarning() << "串口线程等待超时，强制终止（可能有资源泄漏）";
                }
            }
        }
    }

    inline t1_test_auto get_test_auto(QString name){
        if(name == "手动"){
            return t1_test_auto::test_hand;
        }else if(name == "半自动"){
            return t1_test_auto::test_h_auto;
        }else{
            return t1_test_auto::test_auto;
        }
    }

    inline t1_logic_type get_logic_type(QString name){
        if(name == "逻辑与"){
            return t1_logic_type::logic_and;
        }else{
            return t1_logic_type::logic_or;
        }
    }

    inline t1_test_type get_test_type(QString name){
        if(name == "测接点动作"){
            return t1_test_type::action;
        }else{
            return t1_test_type::action_and_return;
        }
    }

    inline t1_test_auto_tpye get_test_type_a(QString name){
        if(name == "递增"){
            return t1_test_auto_tpye::t_a_up;
        }else{
            return t1_test_auto_tpye::t_a_down;
        }
    }

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
    QToolButton* _btn_serial_opera;     // 串口操作
    QToolButton* _btn_power_calcu;      // 功率计算仪表
    QToolButton* _btn_shortout_calcu;   // 短路计算
    QToolButton* _btn_recover_para;     // 恢复默认值
    QToolButton* _btn_up_para;          // 递增数据
    QToolButton* _btn_down_para;          // 递减数据
    QButtonGroup* _btn_test_group;
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

    QTimer* _runtimeTimer = nullptr;
    quint64 _startTime = 0;

    process_1* _process_1 = nullptr;

    serial_ui* _serial_ui;

    QSharedPointer<serial_port> _serialPort;        // 串口智能指针类

    // test interface
private slots:
    void slot_test_start();
    void slot_test_stop();

};

#endif // TEST__1_H
