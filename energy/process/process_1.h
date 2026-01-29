#ifndef PROCESS_1_H
#define PROCESS_1_H

#include "process.h"

// 三相交流电流、电压实验

enum class t1_test_type{
    action,
    action_and_return
};

enum class t1_logic_type{
    logic_and,
    logic_or
};

enum class t1_test_auto{
    test_hand,
    test_auto,
    test_h_auto
};

enum class t1_test_auto_tpye{
    t_a_up,
    t_a_down
};

class process_1 : public process
{
public:
    explicit process_1(QObject *parent = nullptr);

    enum index_map{
        map_value = 0,
        map_change_1,
        map_change_value_1,
        map_max,
        map_phase,
        map_change_2,
        map_change_value_2
    };

    enum index_test_port{
        port_A = 0x80,
        port_B = 0x40,
        port_C = 0x20,
        port_R = 0x10,
        port_a = 0x08,
        port_b = 0x04,
        port_c = 0x02
    };

    void setSerial(serial_port* serial);  // 设置串口指针的 setter 方法

public slots:
    void slot_start(QMap<QString, QList<QVariant>> map,
                    t1_test_type type, t1_logic_type logic, t1_test_auto t_auto, t1_test_auto_tpye t_a_t, QString delay);
    void slot_stop();
    void slot_serial_readyRead();

private:
    int connectRetryCount = 0;
    static constexpr int MAX_CONNECT_RETRY = 3;
    QTimer *timeoutTimer = nullptr;
    QTimer *runtimeTimer = nullptr;
    quint64 startTimestamp = 0;

    QByteArray _frame;

    QString _test_type;

    void attemptConnect();

    // 测试参数
    QMap<QString, QList<QVariant>> _parameter;
    // 返回参数
    t1_test_type _type;
    t1_logic_type _logic;
    t1_test_auto _auto;
    t1_test_auto_tpye _auto_type;
    quint16 _delay_time;

    QSharedPointer<serial_port> _serial;  // 新增：串口成员，使用共享指针

private:
    void test_connect_to_device();
    void test_send_para_to_device();

    QMap<QString, std::function<void()>> _parse_function;

private slots:
    void slot_onTimeout();
    void slot_updateRuntime();

    // process interface
public slots:
    void slot_phase_changed(TestPhase phase) override;

};

#endif // PROCESS_1_H
