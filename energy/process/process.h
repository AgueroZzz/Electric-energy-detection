#ifndef PROCESS_H
#define PROCESS_H

#include <QObject>
#include <QTimer>
#include <QDateTime>

// 测试过程父类

class process : public QObject
{
    Q_OBJECT
public:
    explicit process(QObject *parent = nullptr) : QObject(parent){};

signals:
    void sig_state_changed(QString text, QString color = "#000000");   // 更新状态栏文字+颜色
    void sig_append_log(QString msg);                                 // 追加日志（可选）
    void sig_test_finished(bool success, QString reason = "");       // 测试正常结束或异常结束
    void sig_update_runtime(double seconds);                          // 运行时间更新（可选）
    // 如果需要实时数据给图表
    void sig_new_data(const QVariantMap &data);                       // 或用自定义结构体

public slots:
    virtual void slot_start() = 0;     // 开始测试
    virtual void slot_stop() = 0;      // 立即停止
    // virtual void slot_reset();     // 重置内部状态

protected:
    enum class TestPhase {
        Idle,
        Connecting,
        ParamSetting,
        Running,
        Finishing,
        Error
    };
    TestPhase currentPhase = TestPhase::Idle;

    bool isRunning() const { return currentPhase != TestPhase::Idle && currentPhase != TestPhase::Error; }
};

#endif // PROCESS_H
