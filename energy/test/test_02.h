#ifndef TEST__2_H
#define TEST__2_H

#include "test.h"
#include "ui/test02/ui_002.h"
#include "charts/dc_chart.h"

class test_02 : public test
{
public:
    test_02(quint16 test_id, QWidget *parent = nullptr);

    ~test_02(){
        // if (_process_1) {
        //     _process_1->slot_stop();
        // }
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

    // 顶部/中部/底部Widget
    QWidget* _top_widget;
    ui_002* _ui_002;
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
    QToolButton* _btn_reset_test;     // 数据复位
    QToolButton* _btn_fdq;              // 放大器

    serial_ui* _serial_ui;

    QSharedPointer<serial_port> _serialPort;        // 串口智能指针类
};

#endif // TEST__2_H
