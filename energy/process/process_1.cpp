#include "process_1.h"
#include "serial/serial_port.h"

extern serial_port* _serial;

process_1::process_1(QObject *parent)
    : process{parent}
{
    timeoutTimer = new QTimer();
    timeoutTimer->setSingleShot(true);
    connect(timeoutTimer, &QTimer::timeout, this, &process_1::slot_onTimeout);

    runtimeTimer = new QTimer();
    runtimeTimer->setInterval(100);
    connect(runtimeTimer, &QTimer::timeout, this, &process_1::slot_updateRuntime);
}

void process_1::slot_start(QMap<QString, QList<QVariant> > map, t1_test_type type, t1_logic_type logic, t1_test_auto t_auto, t1_test_auto_tpye t_a_t, QString delay)
{
    if (isRunning()) return;

    _parameter = map;
    _type = type;
    _logic = logic;
    _auto = t_auto;
    _auto_type = t_a_t;
    _delay_time = delay.toUInt();
    QObject::connect(this, &process_1::sig_phase_changed, this, &process_1::slot_phase_changed, Qt::DirectConnection);
    set_TestPhase(TestPhase::Connecting);
}

void process_1::slot_stop()
{
    timeoutTimer->stop();
    runtimeTimer->stop();
    currentPhase = TestPhase::Idle;
    emit sig_state_changed("已停止", "#7f8c8d");
}

void process_1::attemptConnect()
{
    if (connectRetryCount >= MAX_CONNECT_RETRY) {
        currentPhase = TestPhase::Error;
        runtimeTimer->stop();
        emit sig_state_changed("联机失败", "#c0392b");
        emit sig_test_finished(false, "连续3次联机未成功");
        return;
    }

    QByteArray cmd = QByteArray::fromHex("01FF");
    _serial->slot_send_msg_to_serial(cmd);

    timeoutTimer->start(_delay_time);
}

void process_1::test_connect_to_device()
{
    connectRetryCount = 0;
    emit sig_state_changed("正在联机...", "#e67e22");
    startTimestamp = QDateTime::currentMSecsSinceEpoch();
    runtimeTimer->start();

    attemptConnect();

    return;
}

void process_1::test_send_para_to_device()
{
    QByteArray frame;
    frame.append(QByteArray::fromHex("2202"));      // 字节数+交流实验
    frame.append(QByteArray::fromHex("FF14"));      // 暂时未知
    // Ux幅值
    qDebug() << floatToHexLE(_parameter["Ux"][index_map::map_value].toFloat());
}

void process_1::slot_onTimeout()
{
    _frame = _serial->get_serial_port_data();
    if(_frame == QByteArray::fromHex("AA")){
        timeoutTimer->stop();
        set_TestPhase(TestPhase::Running);
        emit sig_state_changed("联机成功", "#27ae60");
        return;
    }
    connectRetryCount++;
    _serial->clear_serial();
    attemptConnect();
}

void process_1::slot_updateRuntime()
{
    double sec = (QDateTime::currentMSecsSinceEpoch() - startTimestamp) / 1000.0;
    emit sig_update_runtime(sec);
}

void process_1::slot_phase_changed(TestPhase phase)
{
    if(phase == TestPhase::Idle){
        return;
    }else if(phase == TestPhase::Connecting){
        test_connect_to_device();
    }else if(phase == TestPhase::Running){

    }else if(phase == TestPhase::Finishing){

    }else if(phase == TestPhase::Error){
        return;
    }
}

// void process_1::slot_thread_start()
// {

// }

// void process_1::slot_thread_stop()
// {

// }
