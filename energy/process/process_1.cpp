#include "process_1.h"
#include "serial/serial_port.h"

extern serial_port* _serial;

process_1::process_1(QObject *parent)
    : process{parent}
{
    timeoutTimer = new QTimer(this);
    timeoutTimer->setSingleShot(true);
    connect(timeoutTimer, &QTimer::timeout, this, &process_1::slot_onTimeout);

    runtimeTimer = new QTimer(this);
    runtimeTimer->setInterval(100);
    connect(runtimeTimer, &QTimer::timeout, this, &process_1::slot_updateRuntime);
}

void process_1::slot_start(QMap<QString, QList<QVariant> > map, t1_test_type type, t1_logic_type logic, t1_test_auto t_auto, t1_test_auto_tpye t_a_t)
{
    if (isRunning()) return;

    currentPhase = TestPhase::Connecting;
    connectRetryCount = 0;

    emit sig_state_changed("正在联机...", "#e67e22");
    emit sig_append_log("开始测试流程 → 阶段：联机");

    startTimestamp = QDateTime::currentMSecsSinceEpoch();
    runtimeTimer->start();

    // 联机测试
    attemptConnect();
}

void process_1::slot_stop()
{
    timeoutTimer->stop();
    runtimeTimer->stop();
    currentPhase = TestPhase::Idle;
    emit sig_state_changed("已停止", "#7f8c8d");
    emit sig_append_log("测试被手动停止");
}

void process_1::attemptConnect()
{
    if (connectRetryCount >= MAX_CONNECT_RETRY) {
        currentPhase = TestPhase::Error;
        runtimeTimer->stop();
        emit sig_state_changed("联机失败", "#c0392b");
        emit sig_test_finished(false, "连续3次联机未成功");
        emit sig_append_log("联机失败：达到最大重试次数");
        return;
    }

    QByteArray cmd = QByteArray::fromHex("01FF");

    _serial->slot_send_msg_to_serial(cmd);

    emit sig_append_log(QString("发送联机命令 %1 (第%2次)")
                            .arg(cmd.toHex(' ').toUpper())
                            .arg(connectRetryCount + 1));

    timeoutTimer->start(1000);
}

void process_1::slot_onSerialData(const QByteArray &data)
{
    if (currentPhase != TestPhase::Connecting) return;

    if (data.contains(char(0xAA))) {
        timeoutTimer->stop();
        currentPhase = TestPhase::ParamSetting;  // 进入下一步
        emit sig_state_changed("联机成功", "#27ae60");
        emit sig_append_log("收到 0xAA，应答成功");
    }
}

void process_1::slot_onTimeout()
{
    _frame.clear();
    _frame = _serial->get_serial_port_data();
    if(_frame == QByteArray::fromHex("AA")){
        timeoutTimer->stop();
        currentPhase = TestPhase::ParamSetting;  // 进入下一步
        emit sig_state_changed("联机成功", "#27ae60");
        emit sig_append_log("收到 0xAA，应答成功");
        return;
    }
    connectRetryCount++;
    attemptConnect();
}

void process_1::slot_updateRuntime()
{
    double sec = (QDateTime::currentMSecsSinceEpoch() - startTimestamp) / 1000.0;
    emit sig_update_runtime(sec);
}
