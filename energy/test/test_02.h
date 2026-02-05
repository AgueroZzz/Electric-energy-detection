#ifndef TEST__2_H
#define TEST__2_H

#include "test.h"
#include "ui/test02/ui_002.h"
#include "process/process_2.h"
#include "charts/dc_chart.h"


class test_02 : public test
{
public:
    test_02(quint16 test_id, QWidget *parent = nullptr);

    ~test_02(){
        if (_process_2) {
            _process_2->slot_stop();
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

    inline t2_test_auto get_test_auto(QString name){
        if(name == "手动"){
            return t2_test_auto::test_hand;
        }else if(name == "自动加"){
            return t2_test_auto::test_auto_up;
        }else{
            return t2_test_auto::test_auto_down;
        }
    }

    inline t2_test_type get_test_type(QString name){
        if(name == "测接点动作"){
            return t2_test_type::action;
        }else{
            return t2_test_type::action_and_return;
        }
    }

    inline quint16 get_result_index(QString name){
        if(name == "A"){return 0;}
        else if(name == "B"){return 1;}
        else if(name == "C"){return 2;}
        else if(name == "R"){return 3;}
        else if(name == "a"){return 4;}
        else if(name == "b"){return 5;}
        else if(name == "c"){return 6;}
        else{
            return 0;
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
    ui_002* _ui_002;
    dc_chart* _dc;
    QWidget* _state_widget;

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
    QToolButton* _btn_fdq;              // 放大器

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

    process_2* _process_2 = nullptr;

    serial_ui* _serial_ui;

    QSharedPointer<serial_port> _serialPort;        // 串口智能指针类

private slots:
    void slot_test_start();
    void slot_test_stop();
};

#endif // TEST__2_H
