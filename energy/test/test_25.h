#ifndef TEST_25_H
#define TEST_25_H

#include "test.h"
#include "ui/test25/ui_025.h"
#include "process/process_25.h"
#include "charts/ac_u_six_chart.h"

// test25:六相交流电压实验

class test_25 : public test
{
public:
    test_25(quint16 test_id, QWidget *parent = nullptr);

    ~test_25(){
        if (_process_25) {
            _process_25->slot_stop();
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

    inline void connect_test_to_process(test_25* test, process_25* process){
        QObject::connect(process, &process::sig_state_changed, test, [test](QString text, QString color){
            test->_state_label->setText(text);
            test->_state_label->setStyleSheet(QString("color:%1; font-weight:bold;").arg(color));
        });

        QObject::connect(process, &process::sig_update_runtime, test, [test](double sec){
            test->_runtime_second->setText(QString::asprintf("%.2f", sec));
        });

        QObject::connect(process, &process::sig_test_finished, test, [test](bool ok, QString reason){
            test->_btn_start_test->setChecked(false);
            test->_btn_end_test->setChecked(true);
            if (!ok) {
                test->setState(TestState::Error);
                QMessageBox::warning(test, "测试异常", reason);
            } else {
                test->setState(TestState::Idle);
            }
        });
        QObject::connect(process, &process_25::sig_frame_parse_result, test, &test_25::slot_frame_parse_result);
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
    ui_025* _ui_025;
    ac_u_six_chart* _current;
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

    // process_25* _process_25 = nullptr;
    QPointer<process_25> _process_25;

    serial_ui* _serial_ui;

    QSharedPointer<serial_port> _serialPort;        // 串口智能指针类

private slots:
    void slot_test_start();
    void slot_test_stop();
};

#endif // TEST_25_H
