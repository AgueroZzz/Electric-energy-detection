#ifndef PROCESS_H
#define PROCESS_H

#include <QObject>
#include <QTimer>
#include <QDateTime>
#include <QThread>
#include "serial/serial_port.h"

// 测试过程父类
enum class TestPhase {
    Idle,
    Connecting,
    ParamSetting,
    Running,
    Finishing,
    Error
};

class process : public QObject
{
    Q_OBJECT
public:
    explicit process(QObject *parent = nullptr) : QObject(parent){};

    inline void set_TestPhase(TestPhase phase) {
        currentPhase = phase;
        emit sig_phase_changed(phase);
    }

    inline QByteArray intToLittleEndianHex(qint16 value) {
        QByteArray byteArray(reinterpret_cast<const char*>(&value), sizeof(value));
        return byteArray;
    }

signals:
    void sig_state_changed(QString text, QString color = "#000000");   // 更新状态栏文字+颜色
    void sig_append_log(QString msg);                                 // 追加日志
    void sig_test_finished(bool success, QString reason = "");       // 测试正常结束或异常结束
    void sig_update_runtime(double seconds);                          // 运行时间更新
    void sig_new_data(const QVariantMap &data);                       // 或用自定义结构体
    void sig_phase_changed(TestPhase phase);
    void sig_send_msg_to_serial(const QByteArray& msg);                    // 向串口发送数据

public slots:
    virtual void slot_phase_changed(TestPhase phase) = 0;

protected:
    TestPhase currentPhase = TestPhase::Idle;

    bool isRunning() const { return currentPhase != TestPhase::Idle && currentPhase != TestPhase::Error; }
};

#endif // PROCESS_H
