#ifndef PROCESS_H
#define PROCESS_H

#include <QObject>
#include <QTimer>
#include <QDateTime>
#include <QThread>
#include <QtEndian>
#include "serial/serial_port.h"

// 测试过程父类
enum class TestPhase {
    Idle,               // 空闲
    Connecting,         // 连接
    ParamSetting,       // 参数设置
    Running,            // 运行
    Finishing,          // 完成
    Error               // 错误
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

    inline quint32 parseActionTime(const QByteArray& frame){
        return  (quint8(frame[3])) |
               ((quint8(frame[4])) << 8) |
               ((quint8(frame[5])) << 16);
    }

    // 将int转换为小端三字节
    inline QByteArray intToThreeBytesLittleEndian(int value) {
        QByteArray result;
        result.resize(3);

        // 确保只取低24位
        quint32 data = static_cast<quint32>(value) & 0xFFFFFF;

        // 转换为小端格式
        qToLittleEndian(data, reinterpret_cast<uchar*>(result.data()));

        // 只取前3字节（小端模式下，低字节在前）
        return result.left(3);
    }

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

    QTimer *runtimeTimer = nullptr;
    quint64 startTimestamp = 0;             // 开始计时为0

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
    void slot_updateRuntime(){
        double sec = (QDateTime::currentMSecsSinceEpoch() - startTimestamp) / 1000.0;
        emit sig_update_runtime(sec);
    };

protected:
    TestPhase currentPhase = TestPhase::Idle;

    bool isRunning() const { return currentPhase != TestPhase::Idle && currentPhase != TestPhase::Error; }
};

#endif // PROCESS_H
