#ifndef PROCESS_26_H
#define PROCESS_26_H

#include "process.h"

enum class t26_test_type{
    action,
    action_and_return
};

enum class t26_test_auto{
    test_hand,
    test_auto_up,
    test_auto_down
};

class process_26 : public process
{
    Q_OBJECT

    enum index_map{
        map_value = 0,
        map_change_1,
        map_change_value_1,
        map_max,
        map_phase,
        map_change_2,
        map_change_value_2
    };

    enum class FrameType{
        f_action = 0x10,
        f_return = 0x20
    };
public:
    explicit process_26(QObject *parent = nullptr);
    void setSerial(serial_port* serial);  // 设置串口指针的 setter 方法

public slots:
    void slot_start(QMap<QString, QList<QVariant>> map,
                    t26_test_type type, t26_test_auto auto_type, QString delay);
    void slot_stop();
    void slot_serial_readyRead();

    // process interface
public slots:
    void slot_phase_changed(TestPhase phase) override;

signals:
    void sig_frame_parse_result(const QStringList& result);

private:
    int connectRetryCount = 0;
    static constexpr int MAX_CONNECT_RETRY = 3;
    QTimer *timeoutTimer = nullptr;
    QByteArray _frame;
    QString _test_type;
    QMap<QString, QList<QVariant>> _parameter;      // 测试参数
    t26_test_type _type;                            // 测试类型（动作/返回）
    t26_test_auto _auto_type;                       // 测试方式（手动/自动加/自动减）
    quint16 _delay_time;
    QSharedPointer<serial_port> _serial;            // 串口共享指针
    QMap<QString, std::function<void()>> _parse_function;       // 解析函数分发map

private:
    void test_connect_to_device();
    void test_send_para_to_device();
    void attemptConnect();
    bool frame_parse(QByteArray frame);

private slots:
    void slot_onTimeout();
};

#endif // PROCESS_26_H
