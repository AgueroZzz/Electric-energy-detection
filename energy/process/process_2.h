#ifndef PROCESS_2_H
#define PROCESS_2_H

#include "process.h"

enum class t2_test_type{
    action,
    action_and_return
};

enum class t2_test_auto{
    test_hand,
    test_auto_up,
    test_auto_down
};

class process_2 : public process
{
    Q_OBJECT
public:
    explicit process_2(QObject *parent = nullptr);

    enum index_map{
        map_value = 0,
        map_change_1,
        map_change_value_1,
        map_max
    };

    enum class FrameType{
        f_action = 0x10,
        f_return = 0x20
    };

    void setSerial(serial_port* serial);  // 设置串口指针的 setter 方法

public slots:
    void slot_start(QMap<QString, QList<QVariant>> map,
                    t2_test_type type, t2_test_auto, QString delay);
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
    QTimer *runtimeTimer = nullptr;
    quint64 startTimestamp = 0;
    QByteArray _frame;
    QString _test_type;
    // 测试参数
    QMap<QString, QList<QVariant>> _parameter;
    // 返回参数
    t2_test_type _type;
    t2_test_auto _auto_type;
    quint16 _delay_time;
    QSharedPointer<serial_port> _serial;  // 串口共享指针
    QMap<QString, std::function<void()>> _parse_function;       // 解析函数分发map

private:
    void test_connect_to_device();
    void test_send_para_to_device();
    void attemptConnect();
    void frame_parse(QByteArray frame);

private:
    // 工具函数:判断端口
    inline QString parsePort(quint8 portByte){
        switch (portByte) {
        case 0x80: return "A";
        case 0x40: return "B";
        case 0x20: return "C";
        case 0x10: return "R";
        case 0x08: return "a";
        case 0x04: return "b";
        case 0x02: return "c";
        default:   return "UnKnow";
        }
    }
};

#endif // PROCESS_2_H
