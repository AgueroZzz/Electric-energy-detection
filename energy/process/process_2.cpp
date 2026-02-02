#include "process_2.h"

process_2::process_2(QObject *parent)
    : process{parent}
{}

void process_2::setSerial(serial_port *serial)
{
    _serial.reset(serial);  // 使用 reset 设置共享指针
    QObject::connect(this, &process_2::sig_send_msg_to_serial, _serial.data(), &serial_port::slot_send_msg_to_serial, Qt::QueuedConnection);
    QObject::connect(_serial.data(), &serial_port::sig_serial_readyRead, this, &process_2::slot_serial_readyRead, Qt::QueuedConnection);
}

void process_2::slot_start(QMap<QString, QList<QVariant> > map, t2_test_type type, t2_test_auto auto_type, QString delay)
{
    if (isRunning()) return;

    _parameter = map;
    _type = type;
    _auto_type = auto_type;
    _delay_time = delay.toUInt();
    QObject::connect(this, &process_2::sig_phase_changed, this, &process_2::slot_phase_changed, Qt::DirectConnection);
    set_TestPhase(TestPhase::Connecting);
}

void process_2::slot_stop()
{
    timeoutTimer->stop();
    runtimeTimer->stop();
    QByteArray frame;
    frame.append(QByteArray::fromHex("0100"));      // 结束
    emit sig_send_msg_to_serial(frame);
    currentPhase = TestPhase::Idle;
    emit sig_state_changed("已停止", "#7f8c8d");
}

void process_2::slot_serial_readyRead()
{
    if(currentPhase != TestPhase::Running){
        return;
    }
    qDebug() << _serial->get_serial_port_data();
    frame_parse(_serial->get_serial_port_data());
}

void process_2::slot_phase_changed(TestPhase phase)
{
    if(phase == TestPhase::Idle){
        return;
    }else if(phase == TestPhase::Connecting){
        test_connect_to_device();
    }else if(phase == TestPhase::Running){
        test_send_para_to_device();
    }else if(phase == TestPhase::Finishing){

    }else if(phase == TestPhase::Error){
        return;
    }
}

void process_2::test_connect_to_device()
{
    connectRetryCount = 0;
    emit sig_state_changed("正在联机", "#e67e22");
    startTimestamp = QDateTime::currentMSecsSinceEpoch();
    runtimeTimer->start();

    attemptConnect();

    return;
}

void process_2::test_send_para_to_device()
{

}

void process_2::attemptConnect()
{
    if (connectRetryCount >= MAX_CONNECT_RETRY) {
        currentPhase = TestPhase::Error;
        runtimeTimer->stop();
        emit sig_state_changed("联机失败", "#c0392b");
        emit sig_test_finished(false, "连续3次联机未成功");
        return;
    }

    QByteArray cmd = QByteArray::fromHex("01FF");
    emit sig_send_msg_to_serial(cmd);

    timeoutTimer->start(_delay_time);
}

void process_2::frame_parse(QByteArray frame)
{
    QStringList results;
    quint8 dataCount = quint8(frame[0]);
    if(frame.size() != (dataCount + 1)){
        return;             // 帧长度=数据位+1
    }
    quint8 type = quint8(frame[1]);
    if(type == static_cast<quint8>(FrameType::f_action)){           // 动作帧
        results << "action";
    }else if(type == static_cast<quint8>(FrameType::f_return)){     // 返回帧
        results << "return";
    }else{
        return;             // 非法帧
    }
    quint8 portByte = quint8(frame[2]);
    QString port = parsePort(portByte);
    if (port == "UnKnow") {
        return;             // 未知端口，丢弃
    }
    results << port;
    quint32 actionTimeMs = parseActionTime(frame);
    results << QString::number(actionTimeMs);

    emit sig_frame_parse_result(results);
}
