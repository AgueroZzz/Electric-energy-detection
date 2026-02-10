#ifndef TEST_24_H
#define TEST_24_H

#include "test.h"
#include "ui/test24/ui_024.h"
#include "process/process_24.h"
#include "charts/ac_six_chart.h"

// test24:六相交流电流实验

class test_24 : public test
{
public:
    test_24(quint16 test_id, QWidget *parent = nullptr);

    ~test_24(){
        if (_process_24) {
            _process_24->slot_stop();
        }
        if (_serialPort) {
            if (_serialPort->_serial_status == index_serial_status::serial_on) {
                _serialPort->slot_serial_opera(index_serial_status::serial_off, {});
            }
            if (_serialPort->_thread.isRunning()) {
                _serialPort->_thread.quit();

                if (!_serialPort->_thread.wait(3000)) {
                    _serialPort->_thread.terminate();
                    qWarning() << "串口线程等待超时，强制终止（可能有资源泄漏）";
                }
            }
        }
    }

private:
    void init_UI();
    void init_top_widget();                     // 初始化顶部按钮
    void init_chart_widget();                   // 初始化图像
    void init_state_widget();                   // 初始化状态栏

    // 顶部/中部/底部Widget
    QWidget* _top_widget;
    ui_024* _ui_024;
    ac_six_chart* _voltage;
    QWidget* _state_widget;

    // 顶部btn
    QToolButton* _btn_open_para;        // 打开参数按钮
    QToolButton* _btn_save_para;        // 保存参数按钮
    QToolButton* _btn_print_test;       // 打印测试记录
    QToolButton* _btn_serial_opera;     // 串口操作
    QToolButton* _btn_up_para;          // 递增数据
    QToolButton* _btn_down_para;        // 递减数据
    QToolButton* _btn_recover_para;     // 恢复默认值
    QButtonGroup* _btn_test_group;
    QToolButton* _btn_start_test;       // 开始实验
    QToolButton* _btn_end_test;       // 停止实验

    // 图标btn
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

    process_24* _process_24 = nullptr;

    serial_ui* _serial_ui;

    QSharedPointer<serial_port> _serialPort;        // 串口智能指针类

private slots:
    void slot_test_start();
    void slot_test_stop();
};

#endif // TEST_24_H
